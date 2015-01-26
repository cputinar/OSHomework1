#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

void connect(){
  pid_t p1,p2; //Will be storing the process IDs for 3 processes as well as a temp id to sort out initial id assignment
  int fd[2], compout;
  char input[100], oldinput[100], firstinput[100];
  int i;

  pipe(fd);

  if((p1 = fork()) == -1)
  {
    perror("first fork failed");
    exit(1);
  } 
  if(p1 == 0)
  {//CHILD
    if((p2 = fork()) == -1)
    {
      perror("second fork failed");
      exit(1);
    } 
    if(p2 == 0)
    {//GrandChild
    	sleep(2);
    	read(fd[0], input, sizeof(input));
    	for(i=0;i<(sizeof(input));i++)
    	{
    		input[i] = toupper(input[i]);
    	}
    	printf("%s\n",input);
    	write(fd[1], input, (strlen(input)+1));
    	printf("Ending Process Three. Goodbye...\n");
    	exit(0);
    }
    else
    {//Child
    	sleep(1);
    	read(fd[0], input, sizeof(input));
    	strrev(input);
    	printf("%s\n", input);
		write(fd[1], input, (strlen(input)+1));
		strcpy(oldinput,input);
    	sleep(1);
    	read(fd[0], input, sizeof(input));
    	strcat(input,oldinput);
    	printf("%s\n",input);
    	write(fd[1], input, (strlen(input)+1));
    	printf("Ending Process Two. Farewell..\n");
    	exit(0);
    }
  }
  else
  {//Parent
  printf("connect\nPlease enter a string:" );
  scanf("%s", input);
  printf("%s\n", input );
  write(fd[1], input, (strlen(input)+1));
  strcpy(firstinput,input);
  sleep(4);
  read(fd[0], input, sizeof(input));
  compout = strcmp(firstinput,oldinput);
  printf("The result of the compare program is :%d\n", compout);
  printf("Ending Process One. Later.\n");
  exit(0);
  }

}

int main(){
  connect();
  return 0;
}
