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

void lower_string(char *string){
   while(*string)
   {
      if ( *string >= 'A' && *string <= 'Z' )
      {
         *string = *string + 32;
      }
      string++;
   }
}

char* add_spaces(char * string){
	char * new_str ;
	if((new_str = malloc(strlen(string)+3)) != NULL){
		new_str[0] = '\0';   // ensures the memory is an empty string
		strcat(new_str," ");
		strcat(new_str,string);
		strcat(new_str," ");
	}

	return new_str;
}

char* add_endl(char * string)
{
	char * new_str ;
	if((new_str = malloc(strlen(string)+3)) != NULL){
		new_str[0] = '\0';   // ensures the memory is an empty string
		strcat(new_str," ");
		strcat(new_str,string);
		strcat(new_str,"\n");
	}

	return new_str;
}

int contains(char *line, char* word, char* options, int *first_time) {

	int k = 0;
	if (*first_time == 1) {
		while (options[k] != '\0') {
			switch(options[k]) {
				case 'i':
					lower_string(line);
					lower_string(word);
					break;
				case 'w':
					strcpy(word,add_spaces(word));
					break;
				default:
					break;
			}

			k++;
		}

		*first_time = 0;
	}

	int i = 0;
	int j = 0;

	while(line[i] != '\n') {
		if (line[i] == word[0]) {
			j = 1;
			i++;
			while(word[j] != '\0') {
				if (line[i] != word[j]) {
					break;
				}
				i++;
				j++;
			}

			if (word[j] == '\0') {
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


	char fileName[50] = "../testfiles/test1.txt";
    FILE* file = fopen(fileName, "r");
    char line[256];
	char word[15] = "An";
	char options[6] = "niw";
	int ft = 1;
	int k = 0;
	int line_number = 0;
	int hit_count = 0;

	while (options[k] != '\0') {
		switch(options[k]) {
			case 'n':
				while (fgets(line, sizeof(line), file)) {
					line_number++;
					if (contains(line, word, options, &ft) == 1)
						printf("%d:%s", line_number, line);
				}
				line_number=0;
				break;
			case 'c':
				while (fgets(line, sizeof(line), file)) {
					if (contains(line, word, options, &ft) == 1)
						hit_count++;
				}
				printf("%d\n", hit_count);
				hit_count = 0;
				break;
			default:
			    while (fgets(line, sizeof(line), file)) {
					if (contains(line, word, options, &ft) == 1)
						printf("%s", line);
    			}
				break;
		}

		k++;
	}

    fclose(file);

    exit(0);
}