#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define true 1
#define false 0
#define QUIT_CODE 101 //Exit codes starts from 101 and 100 is for "continue". Used in initEditor

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

uint8_t command__out(fileState* workspace_file, int from, int through) {}

uint8_t writeFile(fileState* newFile) {

}

uint8_t commandInput(fileState* file, char input){
	if(input == 'q'){
		printf("You wrote q, so we have to exit. Bye!\n");
		return QUIT_CODE;
	}
	
	if (input == 'w') {
		printf("you wrote w");
		int write_code = writeFile
		return 
	} 
	
	return 100;
}

int initEditor(){
	printf("The editor has been started succesfully\n");

	editorState inState;
	fileState openFileState;

	while(1){
		char inp = getc(stdin);
		uint8_t inputStatus = commandInput(inp);
		if(inputStatus != 100) {
			break;
		}
	}

}
