#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define true 1
#define false 0
#define MAX_LINE_LENGTH 2048 //At the moment it will be enough to use 2kb lines
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
	system("clear");
}

uint8_t command__out(fileState* workspace_file, int from, int through) {

}

uint8_t command__c() {
	cleanScreen();
}

uint8_t command__rma(fileState* workspace_file, int line, int from) {
	workspace_file->flc[line][from] = '\0';
}

uint8_t command__ins(fileState* workspace_file, int line, int position) {
	
}

uint8_t command__rm(fileState* workspace_file, int line, int from, int through) {

}

uint8_t command__w(fileState* workspace_file) {

}

uint8_t command__h() {
	printf("This list of commands shows small list of commands and some things, which these commands need, but doesn't show more info, than this, because else this list won't fit viewport on some machines. In order to see better help menu, write mh and visit github or start in-mh application\n\nlist:\n\nh - show this menu\n\nw - write file\n\nq - quit\n\nrm - remove area.\t{after writting this command and pressing enter} [line] [start position] [end position]\nrma - remove after.\t{after writting this command and pressing enter} [line] [start position]\n\nins - insert.\t{after pressing enter} [line] [position]\t{after pressing enter} [line, which you wanna insert]\n");
}

uint8_t command__mh() {
	printf("Not ready yet... You can quit in text editor and start in-mh in order to see more info about application\n");
}

uint8_t commandInput(fileState* workspace_file, char* input){
	uint8_t state = 0;
	if(strcmp(input, "q")==0){
		//printf("You wrote q, so we have to exit. Bye!\n");
		printf("Bye!\n");
		return QUIT_CODE;
	}
	
	//printf("%d", strcmp(input, "q"));

	if (strcmp(input, "w")==0) {
		//printf("you wrote w\n");
		state = 1;
		//int write_code = writeFile(file)
	} 

	if (strcmp(input, "h")==0) {
		//printf("you wrote h\n");
		command__h();
		state = 1;
	}

	if (strcmp(input, "ins")==0) {
		//printf("you wrote ins\n");
		state = 1;
	}

	if (strcmp(input, "rma")==0){
		//printf("you wrote rma\n");
		state = 1;
	}

	if (strcmp(input, "rm")==0) {
		//printf("you wrote rm\n");
		state = 1;
	}

	if (strcmp(input, "out")==0){
		//printf("you wrote out\n");
		state = 1;
	}

	if (strcmp(input, "c")==0) {
		command__c();
		state = 1;
	}

	if (strcmp(input, "mh")==0) {
		command__mh();
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
		if(fgets(inp, 128, stdin)==NULL){
			printf("^D\n");
			return 0;
		};
		//printf("wrote something");
		inp[strcspn(inp,"\n")]=0;
		uint8_t inputStatus = commandInput(open_file_state, inp);
		if(inputStatus != 100) {
			break;
		}
	}
}
