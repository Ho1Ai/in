#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef SEPARATOR
#define SEPARATOR
int separateBySpace(char* input, char** output_thread);

char** getFirstWordBySeparator(char* input, char** output_thread);

int separatableBySpace(char* input);
#endif
