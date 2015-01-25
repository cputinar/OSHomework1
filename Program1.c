#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
//Read file given by path, 
// Print out odd lines and then even lines

//Can use the following commands: open, lseek, read, close
int Odds_then-evens(int argc, const char *argv[]);

int main(){
	Odds_then-evens(int argc, const char *argv[]);
}


int Odds_then-evens(int argc, const char *argv[]){

	char buffer[2048];
	int lineNum=0;
	int i, j;
	char bufferTwo[1];

	//open file
	filedesc = open(path, O_RDONLY);
	//check for errors
	if(filedesc == -1){
		printf("Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	readBuff = read(filedesc, buffer, sizeof(buffer));
	//check for errors
	if(readBuff == -1){
		printf("Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	for(i=0; i < readBuff; i++){
		if((lineNum % 2) == 0){
			bufferTwo[0] = buffer[i];
			writeLine = write(1,bufferTwo, 1);

			if(writeLine == -1){
				printf("Error: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}


			if(buffer[i] == '\n'){
	
				lineNum++;
			}

			if(buffer[i] == EOF){

				exit(EXIT_SUCCESS);
			}
		}
		else {
			if(buffer[i] == '\n'){
				lineNum++;
			}
		}
	}

	i=0; 
	lineNum = 0;
	for(i=0; i < readBuff; i++){
		if((line_number % 2) == 1){
			bufferTwo[0] = buffer[i];
			writeLine = write(1, char_buffer, 1);
			if(writeLine == -1){
				printf("Error: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			if(buffer[i] == '\n'){
				lineNum++;
			}
			if(buffer[i] == EOF){
				exit(EXIT_SUCCESS);
			}
		}
		else {
			if(buffer[i]=='\n'){
				lineNum++;
			}
		}
	}

	close = close(filedesc);
	if(close == -1){
		printf("Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}