#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <math.h>
#include <sys/wait.h>

void process_tree(int rem, int c, pid_t* pidtree)
{
	pid_t pid1,pid2;
    if(rem == 0)
    {
    	if(c == (sizeof(pidtree)))
    	{
    		kill(pidtree[0],SIGCONT);
    	}
    	pause();//Wait until awaken_tree called
		printf("I am process %d, my process identifier is %ld\n",c,((long)getpid()));
		kill((getppid()), SIGCONT);
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
	{//Is Child
		if((pid2 = fork()) == -1)
		{
		printf("%d:",c );
		perror("Fork failed in node");
		exit(1);
		}
		if(pid2 == 0)
		{//Granchild
			process_tree(rem-1,((c*2)+1), pidtree);
		}
		else
		{//Child
			process_tree(rem-1,(c*2), pidtree);
		}
	}
	else
	{//Parent
		pause();//Wait until awaken_tree called
		printf("I am process %d, my process identifier is %ld\n",c,((long)getpid()));
		pause();// Wait for both children to signal their death
		pause();
		kill((getppid()), SIGCONT);
		exit(0);// Kill self upon signalling parent
	}

}

void awaken_tree(pid_t* pidtree)
{
	int i;
	for(i=1;i<(sizeof(pidtree));i++)
	{
		kill(pidtree[i],SIGCONT);
	}
}


void first_node(int n){
	printf("asdasdas12312312\n");
	pid_t pid1,pid2;
	printf("shit\n");
	double height = (double)n + 1;//Figure out height of tree based on the max depth
	printf("YO!\n");
	printf("Height: %lf",height);
	printf("what\n");
	double testpow= pow(2,3);
	printf("Height: %lf",testpow);
	//int finalnum = (int)((pow(2.0,height))-1.0);//Calculate number of nodes in tree
	//printf("Finalnum: %d",finalnum);
	pid_t* pidtree = (pid_t*) malloc(3);//Allocate enough data to hold entire tree
	printf("PID Size: %lu",(sizeof(pidtree)));
	//printf("I am process %d, my process identifier is %ld\n", c, ((long)getpid()));
	pidtree[0]=getpid();
	if((pid1 = fork()) == -1)
	{
		perror("Fork failed in node 1");
		exit(1);
	}
	if(pid1 == 0)
	{//Is Child
		if((pid2 = fork()) == -1)
		{
		perror("Fork failed in node 2");
		exit(1);
		}
		if(pid2 == 0)
		{//Granchild
			process_tree(n-1,3, pidtree);
		}
		else
		{//Child
			process_tree(n-1,2, pidtree);
		}
	}
	else
	{//Parent
		pause();//Wait until the final node is created and signals original ancestor
		sleep(5);//Gives all the processes time to finish forking
		printf("I am process 1, my process identifier is %ld\n",((long)getpid()));
		awaken_tree(pidtree);
		pause();
		pause();
		printf("The tree has been extinguished. It ends with me\n");
		exit(0);
	}	
}
int main(){
	int depth;
	printf("ADASD\n");
	scanf("%d",&depth);
	printf("fuck\n");
	first_node(depth);
	return(0);
}