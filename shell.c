#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>

#define BUF_SIZE 512

int main(int argc, char** argv){
	//Line buffer
	char* line = malloc(BUF_SIZE * sizeof(char));
	char** semicolonCommands = malloc(10 * sizeof(char*));
	int ret = 0, status;
	FILE* stream;

	//Interactive mode
	if(argc == 1){
		stream = stdin;
		printf("spyrou_8583> ");
	}
	//Batch mode
	else if(argc == 2){
		if(!(stream = fopen(argv[1], "r"))){
			fprintf(stderr, "Cannot open batch file \"%s\".", argv[2]);
			return 1;
		}
	}
	//Error
	else{
		fprintf(stderr, "Invalid number of arguments.");
		return 2;
	}

	//Read line and execute commands
	while(fgets(line, BUF_SIZE, stream)){
		int index = 0;
		//Seperate line to semi colons and save the tokens
		semicolonCommands[index] = strtok(line, ";");
		do{
			if (++index >= 10)
				semicolonCommands = realloc(semicolonCommands, (index / 10 + 1) * sizeof(char));

			semicolonCommands[index] = strtok(NULL, ";");
		} while(semicolonCommands[index]);

		//For each semi colon token, seperate it to double ampersands
		for (int i = 0; i < index; i++){
			char* ampersandCommand = strtok(semicolonCommands[i], "&&");
			do{
				//Trim leading and trailing spaces
				while(isspace(ampersandCommand[0]))
					ampersandCommand++;
				int ws = strlen(ampersandCommand) - 1;
				while(isspace(ampersandCommand[ws]))
					ampersandCommand[ws--] = '\0';

				//Terminate if quit was inserted
				if (!strcmp(ampersandCommand, "quit"))
					return 0;

				int pid;
				//Fork in order to execute execvp in child (if comment isn't empty)
				if (ampersandCommand[0] && !(pid = fork())){
					//Store command's arguments in argv
					argv[0] = strtok(ampersandCommand, " ");
					int c = 1;
					while((argv[c++] = strtok(NULL, " ")));
					//Call execvp and get the returned value
					ret = execvp(ampersandCommand, argv);

					//If everything is ok, the next will not be executed
					//Else the error will show up and the child will be killed
					perror(argv[0]);
					exit(ret);
				}
				else
					//Parent waits for the child to finish
					waitpid(pid, &status, 0);

				ampersandCommand = strtok(NULL, "&&");
				//Continue with next command if the previous one returned normally
			} while(ampersandCommand && ret != -1);
		}

		//Print shell prompt
		if (argc == 1)
			printf("spyrou_8583> ");
	}

	return 0;
}
