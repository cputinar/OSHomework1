#include <signal.h>
#include <uninstd.h>
#include <stdio.h>

int main(){

	static struct sigaction act;
	int count = 0;
	pid_t pid, ppid;

	void catchint(int);
	act.sa_handler = catchint;
	sigfillset(&(act.sa_mask));
	sigaction(SIGALRM, &act, NULL);  

	ppid = getpid();
	pid = fork();
	if(pid != 0)
		pid = fork();

	if(ppid != getpid()){
		while(1){
			count++;
		}
	}
	else{
		for(int i = 0; i < 5; i++){
			sleep(1);
			kill(pid1, SIGALRM);
			kill(pid2, SIGALRM);

		}		
	}		
}

void catchint(int sig){
	printf("Count is %d, my pid is %d\n", count, getpid());
	count = 0;
}