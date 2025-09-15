#include <stdint.h>
#include <stdlib.h>
#ifndef EDITOR
#define EDITOR

//#define true 1
//#define false 0
typedef struct {
	int line;
	int linePosition;
	int tabState;
} editorState;

typedef struct {
	int helper__tabState;
	char* filename;
	char** flc; //flc - File Lines Content
	int edited;
} fileState;

void cleanScreen();

uint8_t command__out(fileState* workspace_file, int from, int through);

uint8_t command__c();

uint8_t command__rma(fileState* workspace_file, int line, int from);

uint8_t command__ins(fileState* workspace_file, int line, int position); // then it will ask for text, which you wanna insert. Making comments just not to forget it

uint8_t command__rm(fileState* workspace_file, int line, int from, int through);

uint8_t command__w(fileState* workspace_file);

uint8_t command__h();

uint8_t command__mh();

uint8_t commandInput(fileState* workspace_file, char* input);

int initEditor();

#endif

