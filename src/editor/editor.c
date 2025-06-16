#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define true 1
#define false 0
#define QUIT_CODE 101 //Exit codes starts from 101 and 100 is for "continue". Used in initEditor
//#define WRITE_CODE 102
//#define OUTPUT_CODE 103
//#define INSERT_CODE 104
//#define REMOVE_CODE 105 //both: rma and rm
//#define HELP_OUTPUT_CODE 106

typedef struct {
	int line;
	int linePosition;
} editorState;

typedef struct {
	char* filename;
	char** flc;
	int edited;
} fileState;

void cleanScreen() {

}

uint8_t command__out(fileState* workspace_file, int from, int through) {

}

uint8_t command_w(fileState* workspace_file) {

}

uint8_t commandInput(fileState* workspace_file, char* input){
	uint8_t state = 0;
	if(strcmp(input, "q")==0){
		printf("You wrote q, so we have to exit. Bye!\n");
		return QUIT_CODE;
	}
	
	//printf("%d", strcmp(input, "q"));

	if (strcmp(input, "w")==0) {
		printf("you wrote w\n");
		state = 1;
		//int write_code = writeFile(file)
	} 

	if (strcmp(input, "h")==0) {
		printf("you wrote h\n");
		state = 1;
	}

	if (strcmp(input, "ins")==0) {
		printf("you wrote ins\n");
		state = 1;
	}

	if (strcmp(input, "rma")==0){
		printf("you wrote rma\n");
		state = 1;
	}

	if (strcmp(input, "rm")==0) {
		printf("you wrote rm\n");
		state = 1;
	}

	if (strcmp(input, "out")==0){
		printf("you wrote out\n");
		state = 1;
	}

	if(state!=1) {
		printf("write h in order to see list of supported commands\n");
	}

	return 100;
}

int initEditor(){
	printf("The editor has been started succesfully\n");

	editorState inState;
	fileState* open_file_state = (fileState*)malloc(sizeof(fileState));

	while(1){
		char inp[128];
		//printf("wrote something");
		fgets(inp, 128, stdin);
		//printf("wrote something");
		inp[strcspn(inp,"\n")]=0;
		uint8_t inputStatus = commandInput(open_file_state, inp);
		if(inputStatus != 100) {
			break;
		}
	}
}
