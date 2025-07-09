#include <stdint.h>
#include <stdlib.h>
#ifndef MACRO
#define MACRO

typedef struct {
	char*** swapper;
} macroList;

void addMacro();

void removeMacro();

void getMacroList();

#endif
