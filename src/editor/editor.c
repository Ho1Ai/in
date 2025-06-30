#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define true 1
#define false 0
#define MAX_LINE_LENGTH 2048 //At the moment it will be enough to use 2kb lines
#define QUIT_CODE 101 //Exit codes starts from 101 and 100 is for "continue". Used in initEditor
//#define WRITE_CODE 102
//#define OUTPUT_CODE 103
//#define INSERT_CODE 104
//#define REMOVE_CODE 105 //both: rma and rm
//#define HELP_OUTPUT_CODE 106

//how to write Hello, World in Assembly

typedef struct {
	int line;
	int linePosition;
} editorState;

typedef struct {
	int len;
	char* filename;
	char** flc;
	int edited;
} fileState;

void cleanScreen() {
	system("clear");
}

uint8_t command__out(fileState* workspace_file, int from, int through) {
	int startpos, current, endpos;
	startpos = from;
	endpos = through+1;
	if (from == -1 || through == -1) {
		current = 0;
		while (workspace_file->flc[current] && current < workspace_file->len){
			printf("%d.  %s\n", current, workspace_file->flc[current]);
			current++;
		}
	}else{
		if (endpos>=workspace_file->len-1){
			endpos = workspace_file->len;
		}
		current = startpos;
		while (current<endpos && workspace_file->flc[current]) {
		printf("%d.  %s\n", current, workspace_file->flc[current]);
		current++;
	}}
	return 0;
}

uint8_t command__c() {
	cleanScreen();
}

uint8_t command__rma(fileState* workspace_file, int line, int from) {
	workspace_file->flc[line][from] = '\0';
}

uint8_t command__ins(fileState* workspace_file, int line, int position) {
	
}

uint8_t command__rm(fileState* workspace_file, int line, int from, int through) {
	printf("there is nothing there!\n");
}

uint8_t command__w(fileState* workspace_file) {

}

uint8_t command__h() {
	printf("This list of commands shows small list of commands and some things, which these commands need, but doesn't show more info, than this, because else this list won't fit viewport on some machines. In order to see better help menu, write mh and visit github or start in-mh application\n\nlist:\n\nh - show this menu\n\nw - write file\n\nq - quit\n\nrm - remove area.\t{after writting this command and pressing enter} [line] [start position] [end position]\nrma - remove after.\t{after writting this command and pressing enter} [line] [start position]\n\nins - insert.\t{after pressing enter} [line] [position]\t{after pressing enter} [line, which you wanna insert]\n");
}

uint8_t command__mh() {
	printf("Not ready yet... You can quit in text editor and start in-mh in order to see more info about application\n");
}

void debug_commands__draw(fileState* workspace_file){
	int x=0;
	while(workspace_file->flc[x]){
		printf("%s\n", workspace_file->flc[x]);
		x++;
	}
}

uint8_t commandInput(fileState* workspace_file, char* input){
	uint8_t state = 0;
	if(strcmp(input, "q")==0){
		printf("Bye!\n");
		return QUIT_CODE;
	}

	if (strcmp(input, "w")==0) {
		state = 1;
	} 

	if (strcmp(input, "h")==0) {
		command__h();
		state = 1;
	}

	if (strcmp(input, "ins")==0) {
		state = 1;
	}

	if (strcmp(input, "rma")==0){
		int line, from_pos;
		char ch;
		puts("Give positional arguments: line number and from which position you wanna remove text\n");
		puts("Line number: ");
		scanf("%d", &line);
		while ((ch=getchar())!='\n' && ch != EOF);
		puts("Position (remember, that 1st char in the line has 0th position, 2nd char has 1st position, 3rd has 2nd, 4th has 3rd, etc.): ");
		scanf("%d", &from_pos);
		while((ch=getchar())!='\n' && ch!=EOF);
		command__rma(workspace_file, line, from_pos);
		state = 1;
	}

	if (strcmp(input, "rm")==0) {
		state=1;
		printf("Give positional arguments: line number, start position, last position\n");
		int line_num, start_pos, end_pos;
		char ch;
		puts("line number: ");
		scanf("%d", &line_num);
		while((ch=getchar()) != '\n' && ch != EOF);
		puts("start position: ");
		scanf("%d", &start_pos);
		while((ch=getchar()) != '\n' && ch != EOF);
		puts("end position");
		scanf("%d", &end_pos);
		while((ch=getchar()) != '\n' && ch != EOF);
		command__rm(workspace_file, line_num, start_pos, end_pos); //still not ready
		
		// BUG: it doesn't set state to 1... To be fixed!
		state = 1;
		//printf("%d", state);
	}

	if (strcmp(input, "out")==0){
		//command__out(workspace_file); // still not ready
		char ch;
		int start_line, end_line;
		puts("Give positional arguments: first line, last line. Be careful: In text editor is currently using from-zero indexation, so 1st line has number 0, 2nd line has number 1, etc. If you wanna output full file, you should write -1 and -1 after two next questions\nFirst line: ");
		scanf("%d", &start_line);
		while ((ch=getchar())!='\n' &&ch!=EOF);
		puts("Last line: ");
		scanf("%d", &end_line);
		while((ch=getchar())!='\n' && ch!=EOF);
		putchar('\n');
		//if (workspace_file->flc[start_line]) {
		//	printf("it has read this stuff\n"); // but how?!
		command__out(workspace_file, start_line, end_line);
		//}
		state = 1;
	}

	if (strcmp(input, "c")==0) {
		command__c();
		state = 1;
	}

	if (strcmp(input, "mh")==0) {
		command__mh();
		state = 1;
	}

	if(strcmp(input, "draw")==0) {
		debug_commands__draw(workspace_file);
		state=1;
	}

	if(state!=1) {
		//printf("%d\n", state); // why does it think that it is still 0, but previously it has shown this stuff and it was 1?.. to be fixed! // well, now I see that this stuff works somehow with main while loop
		printf("write h in order to see list of supported commands\n");
	}

	return 100;
}

int inInner__FILE_CONTENT_GETTER(fileState* workspace_file);

void freeMem (fileState* workspace_file);

int initEditor(char* filename){
	if(!filename){
		printf("Couldn't receive filename...\n");
		return 0;
	}
	printf("The editor has been started succesfully\n");
	int file_existence = 1;
	FILE* this_file = fopen(filename,"r");
	if(!this_file){
		printf("No such file. Creating new file.\n");
		FILE* create_file = fopen(filename, "w");
		file_existence = 0;
	}
	editorState inState;
	fileState* open_file_state = (fileState*)malloc(sizeof(fileState)); // called like this only here, because everywhere else I use workspace_file instead
	open_file_state->filename = filename;
	//printf("%s", open_file_state->filename); // just a debug attempt
	int filewrite_test = inInner__FILE_CONTENT_GETTER(open_file_state);
	while(1){
		printf("> ");
		char inp[128];
		//printf("wrote something");
		if(fgets(inp, 128, stdin)==NULL){
			printf("^D\n");
			free(open_file_state);
			fclose(this_file);
			return 0;
		}else{
		//printf("wrote something");
		inp[strcspn(inp,"\n")]=0;
		uint8_t inputStatus = commandInput(open_file_state, inp);
		if(inputStatus != 100) {
			break;
		}}
	}
	
	freeMem(open_file_state);
	
	if (file_existence == 1) {
		fclose(this_file);
	}
	free(open_file_state);
}

int inInner__FILE_CONTENT_GETTER(fileState* workspace_file) {
	//printf("Nothing great\n");
	workspace_file->flc = malloc(sizeof(char*));
	workspace_file->flc[0] = malloc(1);

	FILE* input_file = fopen(workspace_file->filename, "r");
	workspace_file->len=0;
	//printf("Great!\n");
	int line=0, pos = 0; //int multiplier = 1;
	char fileInputBuffer;
	while((fileInputBuffer = fgetc(input_file))!=EOF){
		if(fileInputBuffer!='\n'){
			//printf("this one is - - - %c\n", fileInputBuffer);
			workspace_file->flc[line] = realloc(workspace_file->flc[line], (pos+2)*sizeof(char*));
			workspace_file->flc[line][pos] = fileInputBuffer;
			//printf("reallocated (only char)!\n");
			++pos;
			//++multiplier;
		} else {
			workspace_file->len++;
			// well, why do I reallocate only if this stuff is empty? I have got some questions: maybe, it's better to place a boolean variable, which could save data about \n existence and then check if the char is not EOF so it will just reallocate... Hard to say
			//printf("%d", (line+1)*sizeof(char*));
			workspace_file->flc[line]=realloc(workspace_file->flc[line], (pos+2)*sizeof(char*));
			workspace_file->flc[line][pos]='\0';//somewhere here appears one bug... Very interesting stuff, btw
			workspace_file->flc = realloc(workspace_file->flc, (line+2)*sizeof(char*));
			line++;
			//workspace_file->flc[line+1]=malloc(1);
			pos = 0;
			//multiplier = 1;
			//printf("there is a \\n in a file\n");
		}
		//printf("%c", fileInputBuffer);
	}
}

void freeMem (fileState* workspace_file) {
	int chk = 0;
	while(workspace_file->flc[chk]) {
		//printf("%s\t\t", workspace_file->flc[chk]);
		free(workspace_file->flc[chk]);
		//printf("Cleaning memory %d\n", chk);
		chk++;
	}
	//free(workspace_file->flc);
	//printf("%d\n", sizeof(workspace_file->flc));
	//printf("Cleaning memory, but fully\n");
}
