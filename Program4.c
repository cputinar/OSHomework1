#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int count = 0;

int main(){

	static struct sigaction act;
	pid_t pid, pid2, ppid;

	void catchint(int);
	act.sa_handler = catchint;
	sigfillset(&(act.sa_mask));
	sigaction(SIGALRM, &act, NULL);  

	ppid = getpid();
	pid = fork();
	if(pid != 0)
		pid2 = fork();

	if(ppid != getpid()){
		while(1){
			count++;
		}
	}
	else{
		int i = 0;
		for(i; i < 5; i++){
			sleep(1);
			kill(pid, SIGALRM);
			kill(pid2, SIGALRM);

		}		
	}
	return 0;		
}

void catchint(int sig){
	printf("Count is %d, my pid is %d\n", count, getpid());
	count = 0;
}
