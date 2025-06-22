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

//how to write Hello, World in Assembly

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
	int startpos, current, endpos;
	if (from == -1 || through == -1) {
		current = 0;
		while (workspace_file->flc[current][0]!='\0'){
			printf("%s", workspace_file->flc[current]);
		}
	}else{
		current = startpos;
		while (current<endpos) {
		printf("%s", workspace_file->flc[current]);
		current++;
	}}
	return 0;
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
	printf("there is nothing there!\n");
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
		printf("Bye!\n");
		return QUIT_CODE;
	}

	if (strcmp(input, "w")==0) {
		state = 1;
	} 

	if (strcmp(input, "h")==0) {
		command__h();
		state = 1;
	}

	if (strcmp(input, "ins")==0) {
		state = 1;
	}

	if (strcmp(input, "rma")==0){
		state = 1;
	}

	if (strcmp(input, "rm")==0) {
		state=1;
		printf("Give positional arguments: line number, start position, last position\n");
		int line_num, start_pos, end_pos;
		puts("line number: ");
		scanf("%d", &line_num);
		puts("start position: ");
		scanf("%d", &start_pos);
		puts("end position");
		scanf("%d", &end_pos);
		command__rm(workspace_file, line_num, start_pos, end_pos); //still not ready
		
		// BUG: it doesn't set state to 1... To be fixed!
		state = 1;
		//printf("%d", state);
	}

	if (strcmp(input, "out")==0){
		//command__out(); // still not ready
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
		//printf("%d\n", state); // why does it think that it is still 0, but previously it has shown this stuff and it was 1?.. to be fixed! // well, now I see that this stuff works somehow with main while loop
		printf("write h in order to see list of supported commands\n");
	}

	return 100;
}

int initEditor(char* filename){
	if(!filename){
		printf("Couldn't receive filename...\n");
		return 0;
	}
	printf("The editor has been started succesfully\n");
	int file_existence = 1;
	FILE* this_file = fopen(filename,"r");
	if(!this_file){
		printf("the file does not exist =(\nCreating new file\n");
		FILE* create_file = fopen(filename, "w");
		file_existence = 0;
	}
	editorState inState;
	fileState* open_file_state = (fileState*)malloc(sizeof(fileState));
	
	while(1){
		printf("> ");
		char inp[128];
		//printf("wrote something");
		if(fgets(inp, 128, stdin)==NULL){
			printf("^D\n");
			free(open_file_state);
			fclose(this_file);
			return 0;
		};
		//printf("wrote something");
		inp[strcspn(inp,"\n")]=0;
		uint8_t inputStatus = commandInput(open_file_state, inp);
		if(inputStatus != 100) {
			break;
		}
	}

	if (file_existence == 1) {
		fclose(this_file);
	}
	free(open_file_state);
}
