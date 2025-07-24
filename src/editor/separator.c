#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int separatableBySpace(char* input){ //return 1-4 - impossible (1 is for command only (no spaces), 2 is for spaces in the beggining, 3 is for many spaces in the end, 4 - there is too many spaces as a separator somewhere), return 0 - possible
	if(strcspn(input, " ") == strlen(input)){
		return 1;
	}

	if(strcspn(input, " ")==0) {
		return 2;
	}	


	if(input[strlen(input)-1] == ' ' && input[strlen(input)-2]==' ') {
		return 3; //well, if there is so many spaces, it will drop 4th error anyway
	}

	if(strcspn(input, "  ")!=strlen(input)) {
		return 4;
	}
	
	return 0;
}
