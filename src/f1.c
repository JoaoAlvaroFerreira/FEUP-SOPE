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

int contains(char *line, char *word) {

	int i = 0;
	int j = 0;

	while(line[i] != '\n') {
		if (line[i] == word[0]) {
			j = 1;
			i++;
			while(word[j] != NULL) {
				if (line[i] != word[j]) {
					break;
				}
				i++;
				j++;
			}

			if (word[j] == NULL) {
				return 1;
			}
		} else
			i++;
	}

	return 0;
}

int main(){

    // //Handling signal
	// struct sigaction action;
	// action.sa_handler = sigint_handler;
	// sigemptyset(&action.sa_mask);
	// action.sa_flags = 0;
	// signal(SIGINT, sigint_handler);

    // while(1) {
    //     sleep(1);
    // }

	// //TESTING contains
	// char line[] = "Somebody once told me the world is gonna roll me\n";
	// char word[] = "body";

	//  if (contains(&line, &word) == 1)
	// 	printf("%s", line);
	// else
	// 	printf("Not found\n");

	char const* const fileName = "../testfiles/test1.txt";
    FILE* file = fopen(fileName, "r");
    char line[256];
	char word[] = "body";

    while (fgets(line, sizeof(line), file)) {
		if (contains(&line, &word) == 1)
			printf("%s", line);
    }

    fclose(file);

    exit(0);
}