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
	struct stat statbuf;
	DIR *dp;
	dp = opendir(path);
	indents++;
	if(!dp){
		printf("Bad dir: %s\n", path);
		return;
	}
	while(d = readdir(dp)){
		if((d->d_ino != 0) && (strcmp(d->d_name, ".") != 0) && (strcmp(d->d_name, "..") != 0)){
			int i = 0;
			for(i; i < indents; i++)
				printf("  ");
			printf("%s\n", d->d_name);
			if(!strcmp(d->d_name, target)){
				printf("Found file %s at path %s\n", target, path);
				exit(0);
			}
			int pathlen = strlen(path);
			int dirlen = strlen(d->d_name);
			char wholepath[pathlen+dirlen+1];
			strcpy(wholepath, path);
			strcat(wholepath, "/");
			strcat(wholepath, d->d_name);
			stat(wholepath, &statbuf);
			if(S_ISDIR(statbuf.st_mode)){
				//printf("%s\n", d->d_name);
				dfs(wholepath, target);
			}
		}
	}

	closedir(dp);
	indents--;
	return;
}

