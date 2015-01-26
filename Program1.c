#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

//Read file given by path, 
// Print out odd lines and then even lines


int main(int argc, char *argv[]){
	char buffer[2048], bufferTwo[256], *path;
	size_t readBuff, writeLine;
	int i, j, closeFile, filedesc, lineNum=0;

	//open up the path
	path = argv[1];

	//open file
	filedesc = open(path, O_RDONLY);
	if(filedesc == -1){ //error checking
		printf("Error is: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	readBuff = read(filedesc, buffer, sizeof(buffer));
	if(readBuff == -1){ //error checking
		printf("Error is: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	for(i=0; i < readBuff; i++){ //first loop for odd numbered lines
		if((lineNum % 2) == 0){ //odd numbered lines
			bufferTwo[0] = buffer[i]; //move line to second buffer

			writeLine = write(1,bufferTwo, 1); //write this
			if(writeLine == -1){ //error checking for write
				printf("Error is: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			
			else if(buffer[i] == '\n'){ 
				lineNum++;
			}

			else if(buffer[i] == EOF){ //reaches end of file, exit
				exit(EXIT_SUCCESS);
			}
		}
		else { //even numbered lines, skip them
			if(buffer[i] == '\n'){
				lineNum++;
			}
		}

	}
	

	lineNum = 0; //reset lineNum
	bufferTwo[0] = '\n'; //add a newline
	write(1, bufferTwo, 1); //write this newline


	for(j=0; j < readBuff; j++){ //second loop for even numbered lines
		if((lineNum % 2) == 1){
			bufferTwo[0] = buffer[j];

			writeLine = write(1, bufferTwo, 1);
			if(writeLine == -1){ //error checking
				printf("Error is: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}

			else if(buffer[j] == '\n'){
				lineNum++;
			}
			else if(buffer[j] == EOF){ //reaches end of file, exit
				exit(EXIT_SUCCESS);
			}
		}

		else { //odd number lines, skip them
			if(buffer[j]=='\n'){
				lineNum++;
			}
		}
	}

	//close the file
	closeFile = close(filedesc);
	if(closeFile == -1){ //error checking
		printf("Error is: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	//program exits successfully
	exit(EXIT_SUCCESS);
}



