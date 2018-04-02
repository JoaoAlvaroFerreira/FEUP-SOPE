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

void sigint_handler(int sig){}

void fileAction(char* dirName, char* name){}

void process_info(char* dirName, struct dirent *direntp, struct stat stat_buf) {}

int main(int argc, char* argv[]){}