#ifndef EDITOR
#define EDITOR

#define true 1
#define false 0
typedef struct {
	int line;
	int linePosition;
} editorState;

typedef struct {
	char* filename;
	char** flc; //flt - File Lines Content
	int edited;
} fileState;

void cleanScreen();

void moveCursor(int direction);

void writeFile();



void initEditor();

#endif

