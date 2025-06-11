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

void moveCursor(int direction);

void writeFile(fileState newFile);

uint8_t input(char* input);

int initEditor();

#endif

