#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
//Read file given by path, 
// Print out odd lines and then even lines

//Can use the following commands: open, lseek, read, close
int Odds_then-evens(char path);

int main(){
	return 0;
}


int Odds_then-evens(char path){
	
	//open file
	filedesc = open(path, O_RDONLY);
	//positions at first char
	lseek(filedesc,0,0);

	char buffer[1];
	read(filedesc, &buffer, sizeof(buffer));

	if(buffer == '\n'){

	}



//every time it hits a newline, print and then lseek the odd line


}