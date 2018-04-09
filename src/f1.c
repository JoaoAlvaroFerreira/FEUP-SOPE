#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

//SOPE

void sigint_handler(int sig) { //main handler

	char c;

	printf("\nAre you sure you want to terminate (Y/N)? ");

	scanf("%c", &c);

	if (c == 'y' || c == 'Y')
		exit(0);
	else if (c == 'n' || c == 'N') {
        fflush(stdin);
		return;
    }
	else {
		printf(" >> ERROR: Character not allowed!");
		sigint_handler(SIGINT);
	}
	return;
}

void fileAction(char* dirName, char* name){}

void process_info(char* dirName, struct dirent *direntp, struct stat stat_buf) {}

int main(){

    	//Handling signal
	struct sigaction action;
	action.sa_handler = sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	signal(SIGINT, sigint_handler);

    while(1) {
        sleep(1);
    }
    exit(0);
}