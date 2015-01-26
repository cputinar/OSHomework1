#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <math.h>
#include <sys/wait.h>

void process_tree(int rem, int c, int finalnum, pid_t* pidtree)
{
	pid_t pid1,pid2,wpid;
    if(rem == 0)
    {
    	if(c == finalnum)
    	{
    		kill(pidtree[0],SIGCONT);
    	}
    	//kill(getpid(),SIGSTOP);//Wait until awaken_tree called
    	sleep(c);
		printf("I am process %d, my process identifier is %ld\n",c,((long)getpid()));
		sleep(finalnum-c);
		printf("Killing process %d, my process identifier is %ld\n",c,((long)getpid()));
		exit(0);// Kill self upon signalling parent
    }
	pidtree[c-1]=getpid();
	if((pid1 = fork()) == -1)
	{
		printf("%d:",c );
		perror("Fork failed in node");
		exit(1);
	}
	if(pid1 == 0)
	{//1st Child
		process_tree(rem-1,(c*2),finalnum, pidtree);
	}
	else
	{//Parent
		if((pid2 = fork()) == -1)
		{
		printf("%d:",c );
		perror("Fork failed in node");
		exit(1);
		}
		if(pid2 == 0)
		{//2nd child
			process_tree(rem-1,((c*2)+1),finalnum, pidtree);
		}
		else
		{//Parent
			//kill(getpid(),SIGSTOP);//Wait until awaken_tree called
			sleep(c);
			printf("I am process %d, my process identifier is %ld\n",c,((long)getpid()));
			while((wpid = wait(NULL)) > 0);//Wait for all children to die
			{
				sleep(1);
			}
			printf("Killing process %d, my process identifier is %ld\n",c,((long)getpid()));
			exit(0);// Kill self upon signalling parent
		}
	}

}

void awaken_tree(pid_t* pidtree, int finalnum)
{
	int i;
	kill(pidtree[1],SIGCONT);
	/*for(i=1;i<finalnum;i++)
	{
		kill(pidtree[i],SIGCONT);
		sleep(1);
	}*/
}


void first_node(int n){
	pid_t pid1,pid2, wpid,*pidtree;
	double height = (double)n + 1;//Figure out height of tree based on the max depth
	int finalnum = (int)((pow(2.0,height))-1.0);//Calculate number of nodes in tree
	pidtree = malloc(finalnum*sizeof(*pidtree));//Allocate enough data to hold entire tree
	//printf("I am process %d, my process identifier is %ld\n", c, ((long)getpid()));
	pidtree[0]=getpid();
	if((pid1 = fork()) == -1)
	{
		perror("Fork failed in node 1");
		exit(1);
	}
	if(pid1 == 0)
	{//Is 1st Child
		process_tree(n-1,2,finalnum, pidtree);
	}
	else
	{//Parent
		if((pid2 = fork()) == -1)
		{
		perror("Fork failed in node 2");
		exit(1);
		}
		if(pid2 == 0)
		{//Is 2nd Child
			process_tree(n-1,3,finalnum, pidtree);
		}
		else
		{//Parent
			//kill(getpid(),SIGSTOP);//Wait until the final node is created and signals original ancestor
			sleep(1);
			printf("I am process 1, my process identifier is %ld\n",((long)getpid()));
			//awaken_tree(pidtree, finalnum);
			while((wpid = wait(NULL)) > 0);//Wait for all children to die
			{
				sleep(1);
			}
			printf("The tree has been dismantled. It ends with me process 1, pid: %ld\n",((long)getpid()));
			exit(0);
		}
	}
}
int main(int argc, char **argv){
	pid_t pid;
	int depth;
	if(argc != 2)
	{
		perror("Wrong amount of arguments: Use \"$program6 depth\" to run program\n");
		exit(1);
	}
	depth = atoi(argv[1]);
	if(depth < 1)
	{
		perror("Invalid parameter depth. Did you enter a number greater than 0?\n");
		exit(1);
	}
	if((pid = fork()) == -1)
	{
		perror("Fork failed in node 1");
		exit(1);
	}
	if(pid == 0)
	{
		first_node(depth);
	}
	else
	{
		wait(NULL);
	}
	return(0);
}