#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char*** swapper;
	char* macro_list_path; // if it has been changed, the final user can write it in .config/inconfig.st by using one of these constructions: "~/..." or "/..." (if the user has something in the root dir)
} macroList;

void addMacro() {} // will also save macro list

void removeMacro() {}

void getMacroList() {}

int loadMacroList() {} // can return 1 if it got an unexpected error
