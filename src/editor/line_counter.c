#include <stdio.h>

int count_lines(char* filename) {
	FILE* file_thread = fopen(filename, "r");
	
	char current_char;
	
	int result = 0;

	while((current_char = fgetc(file_thread))!=EOF) {
		if(current_char == '\n') {
			result++;
			}
		}
	
	printf("%d\n", result);

	fclose(file_thread);
	return result;
	}
