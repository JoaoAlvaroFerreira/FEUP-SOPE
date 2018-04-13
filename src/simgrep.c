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

char* appendChar(char * string, char ch){
	char *str = string;
    char c = ch;

    size_t len = strlen(str);
    char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';

	return str2;
}

char* appendString(char * str1, char* str2){
	char * new_str ;
	if((new_str = malloc(strlen(str1)+strlen(str2)+1)) != NULL){
		new_str[0] = '\0';   // ensures the memory is an empty string
		strcat(new_str,str1);
		strcat(new_str,str2);
	}

	return new_str;
}

char* add_endl(char * string)
{
	char * new_str;
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

void convertOptions(char* args, char* options) {
	char opt[15];

	int i = 0;

	while(args[i] != '\0') {
		if (args[i] == 'n' || args[i] == 'c') {
			opt[0] = args[i];
			break;
		}
		i++;
	}

	i = 0;

		while(args[i] != '\0') {
			if (args[i] == 'i' || args[i] == 'w') {
				strcpy(opt,appendChar(opt, args[i]));
			}
			i++;
	}

	strcpy(options,opt);
}

void readfile(char* fileName, char* word, char* options) {

	char line[256];
	int k = 0;
	int ft = 1;
	int hit_count = 0;

	FILE* file = fopen(fileName, "r");
	int line_number = 0;

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
}

int main(int argc, char *argv[]){

    //Handling signal
	struct sigaction action;
	action.sa_handler = sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	signal(SIGINT, sigint_handler);

	char fileName[50] = "testfiles/test1.txt";
	char word[15] = "An";
	char options_args[15];
	char options[15];
	int i = 0;

	switch(argc) {
		case 1:
			printf("Must specify pattern and file");
			return 0;
		case 2:
			printf("Must specify pattern and file");
			return 0;
		case 3:
			strcpy(word, argv[1]);
			strcpy(fileName, argv[2]);
			break;
		default:
			i = argc-1;
			while(i != 0) {
				if (i == (argc - 1)) {
					strcpy(fileName, argv[i]);
				}
				else if (i == (argc - 2)) {
					strcpy(word, argv[i]);
				}
				else {
					strcpy(options_args, appendString(options_args, argv[i]));
				}
				i--;	
			}
			break;	
	}

	convertOptions(options_args, options);
	readfile(fileName, word, options);

    exit(0);
}