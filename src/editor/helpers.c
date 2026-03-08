#include <stdlib.h>
#include <stdio.h>

int my_itoa(long long number, char** dest) {
	int pos = 0;
	*dest = realloc(*dest, sizeof(char)*15);
	//printf("added zero position");
	while (number) {
		(*dest)[pos++] = number%10+'0';
		number/=10;
		}
	(*dest)[pos] = '\0';
	*dest = realloc(*dest, sizeof(char)*(pos+1));
	pos--;
	int l = 0, r = pos;
	while (l < r) {
		char q = (*dest)[l];
		(*dest)[l] = (*dest)[r];
		(*dest)[r] = q;
		l++;
		r--;
		}
	}
