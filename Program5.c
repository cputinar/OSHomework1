#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void dfs(char*, char*);
int indents = -1;
int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Error: too few arguments\n");
		exit(1);
	}
	dfs(argv[1], argv[2]);
	return 0;	 
}

void dfs(char *path, char *target){
	struct dirent *d;
	DIR *dp;
	dp = opendir(path);
	indents++;
	if(!dp)
		return;
	while(d = readdir(dp)){
		if((d->d_ino != 0) && (strcmp(d->d_name, ".") != 0) && (strcmp(d->d_name, "..") != 0)){
			int i = 0;
			for(i; i < indents; i++)
				printf("\t");
			//printf("%s\n", d->d_name);
			struct stat statbuf;
			stat(d->d_name, &statbuf);
			if(S_ISDIR(statbuf.st_mode)){
				int pathlen = strlen(path);
				int dirlen = strlen(d->d_name);
				char newpath[pathlen+dirlen+1];
				strcpy(newpath, path);
				strcat(newpath, "/");
				strcat(newpath, d->d_name);

				printf("%s\n", d->d_name);
				dfs(newpath, target);
			}
		}
	}

	closedir(dp);
	indents--;
	return;
}

