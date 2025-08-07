#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getOneNum(char symbol) {
	int result;
	switch (symbol) {
		case '1':
			result = 1;
			break;
		case '2':
			result = 2;
			break;
		case '3':
			result = 3;
			break;
		case '4':
			result = 4;
			break;
		case '5':
			result = 5;
			break;
		case '6':
			result = 6;
			break;
		case '7':
			result = 7;
			break;
		case '8':
			result = 8;
			break;
		case '9':
			result = 9;
			break;
		default: // if the symbol is a char, it will return 0, cuz it is not a number
			result = 0;
			break;
	}
	return result;
}

int argToInteger(char* arg){ //in separator file, cuz it is mostly needed for separator nor for editor
	int xi = 0;
	int result = 0; // w/o negatives
	int negative_result = 1; // -1 if negative
	if(arg[0]=='-'){
		xi++;

		negative_result = -1;
	}

	//printf("line len: %d\n", strlen(arg));

	while(arg[xi] && xi<strlen(arg)){
		//printf("%d\n", atoi(&arg[xi]));
		result*=10;
		result+=getOneNum(arg[xi]);	
		xi++;
	}

	//printf("got: %d\n", result);

	return result*negative_result;
}

int separatableBySpace(char* input){ //return 1-4 - impossible (1 is for command only (no spaces), 2 is for spaces in the beggining, 3 is for many spaces in the end, 4 - there is too many spaces as a separator somewhere), return 0 - possible
	if(strcmp(input, "")==0 || input[0] == ' '){
		return 99;
	}

	if(strcspn(input, " ") == strlen(input)){
		return 1;
	}

	if(strcspn(input, " ")==0) {
		//printf("BAD INPUT\n");
		return 2;
	}	


	//printf("%d %d\n", (input[strlen(input)-1] == ' ' && input[strlen(input)-2]==' '), strlen(input));

	if(input[strlen(input)-1] == ' ' && input[strlen(input)-2]==' ') {
		return 3; //well, if there is so many spaces, it will drop 4th error anyway
	} // yeah, logically it is incorrect to do this stuff here, cuz it doesn't work at all, by the way, lmao, but let it be. These codes I'm gonna use only in order to catch errors

	if(input[strcspn(input, " ")]==input[strcspn(input, " ")+1]) { // checks if there is 2 spaces in a row
		puts("there is too many spaces somewhere as a separator.\nTaking first word only.\n");
		return 4;
	}
	
	return 0;
}
/*
int separateBySpace(char* input, char** output_thread){
	 char** outputData = malloc(sizeof(char*));
	 int new_len = 1;
	 int xi = 0;
	 char* separators = strtok(input," ");
	 printf("%s\n", separators);
	 separators = strtok(NULL, " ");
	 printf("%s\n", separators);
}

char** getFirstWordBySeparator(char* input, char** output_thread) {
	printf("%s\n", strtok(input, " "));
	char* command = strtok(input, " ");

	char** return_data = malloc(sizeof(char*));
	return_data[0] = malloc(sizeof(char));
	int new_len = 1;
	int xi = 0;
	while(xi<strlen(command)-1){
		printf("copying - %c\n", command[xi]);
		return_data[0] = realloc(return_data[0], sizeof(char)*new_len);
		return_data[0][xi] = input[xi];
		new_len++;
		xi++;
	}

	return_data[0] = realloc(return_data[0], sizeof(char)*new_len);
	return_data[0][xi] = '\0';

	puts(return_data[0]);

	//output_thread = malloc(sizeof(char*));

	//free(return_data[0]);
	//free(return_data);
	
	//output_thread = malloc(sizeof(char*));
	//output_thread[0] = return_data[0];
	//puts(output_thread[0]);
	//free(return_data);
	//puts(output_thread[0]);
	//output_thread = malloc(sizeof(char*));
	//output_thread[0] = malloc(strlen(return_data[0])+1);
	//strcpy(output_thread[0], return_data[0]);
	//output_thread[0][strlen(return_data[0])] = '\0';
	
	return (return_data);
} */
