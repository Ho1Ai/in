#include <stdint.h>
#include <stdlib.h>
#ifndef MACRO
#define MACRO

typedef struct {
	char*** swapper; //under this word (I mean "macro") I understand just a simple command swapper. So, for example, I could use "insert" instead of "ins" or "lc" instead of "rmln". Standard CLI mode can't give something more... I'll try RAW mode in my future projects... but not in this
} macroList;

void addMacro();

void removeMacro();

void getMacroList();

void writeMacroList();

#endif
