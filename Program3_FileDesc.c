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
#define RD_WR 0666

//File-descriptor-test:  


int main(){
	pid_t childPID;
	char buffer[2048];
	int inputFile, fd, newFD;
	size_t readBuf, newRead;
	
	fd = creat("data", RD_WR); // create file descriptor 
	childPID = fork();
	if(childPID >= 0){ //successful fork
		if(childPID == 0){ //child process
			printf("Value of fd (Child): %d\n", fd);
			printf("Value of new fd (Child): %zd\n", write(fd, "new words", 9));
		}
		else {
			printf("Value of fd (Parent): %d\n", fd);
			printf("Value of new fd (Parent): %d\n", fd);
		} //parent process
	}
	else { //unsuccessful fork
		printf("Fork failed\n");
		exit(EXIT_FAILURE);
	}

	if(close(fd) == -1){
		printf("Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}



