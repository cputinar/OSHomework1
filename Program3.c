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


//Fork-variable-test: 
//File-descriptor-test:  
int Fork_Variable_Test();

int main(){
	Fork_Variable_Test();
	//File-descriptor-test();
	return 0;
}


int Fork_Variable_Test() {
	pid_t childPID;	
	int var = 10;

	childPID = fork();

	if (childPID >= 0){ //successful fork
		if(childPID == 0){ //child process
			printf("Variable value: %d\n", var);
			var++;
			printf("Independent variable value: %d\n", var);
		}
		else { //parent process
			printf("Variable value: %d\n", var);
			var = var+10;
			printf("Independent variable value: %d\n", var);
		}
	}
	else { //unsuccessful fork
		printf("Fork failed\n");
		return 1;
	}
}

/*void File-descriptor-test() {
	pid_t childPID;
	int filedesc;

	fildesc = open("file", )
	childPID = fork();

	if (childPID >= 0){ //successful fork
		if(childPID == 0){ //child process

		}
		else { //parent process

		}
	}
	else { //unsuccessful fork
		printf("Fork failed\n");
		return 1;
	}
}*/