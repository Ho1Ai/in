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

void moveCursor(int direction) {}

void writeFile(fileState newFile) {

}

uint8_t input(char input){
	if(input == 'q'){
		printf("You wrote q, so we have to exit. Bye!\n");
		return QUIT_CODE;
	} 
	
	return 100;
}

int initEditor(){
	printf("The editor has been started succesfully");

	editorState inState;
	fileState openFileState;

	while(1){
		char inp = getchar();
		uint8_t inputStatus = input(inp);
		if(inputStatus != 100) {
			break;
		}
	}

}
