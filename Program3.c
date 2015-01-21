#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>


//Fork-variable-test: 
//File-descriptor-test:  
void Fork-variable-test();
void File-descriptor-test();

int main(){

	return 0;
}


void Fork-variable-test() {
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

void File-descriptor-test() {
	pid_t childPID;

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
}