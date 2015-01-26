#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>


int main(){

	pid_t childPID;	
	int var = 10;

	childPID = fork();

	if (childPID >= 0){ //successful fork
		if(childPID == 0){ //child process
			printf("Dependent Child Value: %d\n", var);
			var++;
			printf("Independent Child Value: %d\n", var);
		}
		else { //parent process
			printf("Dependent Parent Value: %d\n", var);
			var = var+10;
			printf("Independent Parent Value: %d\n", var);
		}
	}
	else { //unsuccessful fork
		printf("Fork failed\n");
		return 1;
	}
}