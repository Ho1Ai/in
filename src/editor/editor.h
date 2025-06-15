#include <stdint.h>
#ifndef EDITOR
#define EDITOR

//#define true 1
//#define false 0
typedef struct {
	int line;
	int linePosition;
} editorState;

typedef struct {
	char* filename;
	char** flc; //flc - File Lines Content
	int edited;
} fileState;

void cleanScreen();

uint8_t command__out(fileState* workspace_file, int from, int through);

uint8_t writeFile(fileState newFile);

uint8_t commandInput(char* input);



int initEditor();

#endif

