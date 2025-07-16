#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_LINE_LENGTH 2048 //At the moment it will be enough to use 2kb lines
#define QUIT_CODE 101 //Exit codes starts from 101 and 100 is for "continue". Used in initEditor
//#define WRITE_CODE 102
//#define OUTPUT_CODE 103
//#define INSERT_CODE 104
//#define REMOVE_CODE 105 //both: rma and rm
//#define HELP_OUTPUT_CODE 106

//how to write Hello, World in Assembly

//I wanna tell you something about vars naming:
//1. xi - variable, which means offset
//2. 99 is an exit code for functions. It may be appeared by inner errors (e.g. u wanna insert something into the line, which has number -12345678)
//3. zita - variable, which means offset (also as xi)

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
	if (from >=-1) { // from can be -1, because if it is -1 (or through is -1) it returns full file
		startpos = from;
	} else {
		printf("Start position can't be less, than -1. Setting start position to 0\n\n");
		startpos = 0;
	}

	if(through >= -1) {
		endpos = through+1;
	} else {
		printf("Unexpected argument as last position. The argument must be equal or above -1\n");
		return 1;
	}
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
	cleanScreen(); //why?..
}







uint8_t command__rma(fileState* workspace_file, int line, int from) {
	//printf("%d\n", strlen(workspace_file->flc[line]));
	if(line < 0) {
		printf("Line number must be between 0 and %d, but you have entered %d. Execution failed\n", workspace_file->len-1, line);
		return 1;
	}
	if(line >= workspace_file->len) {
		printf("Line number is too high. You have only %d lines. Execution failed\n", workspace_file->len);
		return 1;
	}

	if (from >= strlen(workspace_file->flc[line])) {
		printf("Entered number is higher, than line length. Current line length is: %d\n", strlen(workspace_file->flc[line]));
		return 1;
	}

	if (from < 0) {
		printf("Start position can't be less, than 0\n");
	}

	if(from<strlen(workspace_file->flc[line])){
		workspace_file->flc[line][from] = '\0';
		char* tmp_line=malloc(sizeof(char*)*((strlen(workspace_file->flc[line])+1)));
		int xi = 0;
		while(workspace_file->flc[line][xi]){
			tmp_line[xi]=workspace_file->flc[line][xi];
			xi++;
		}
		tmp_line[strlen(workspace_file->flc[line])]='\0';
		free(workspace_file->flc[line]);
		workspace_file->flc[line] = tmp_line;
	//printf("%d\n", strlen(workspace_file->flc[line]));
	}
}






uint8_t command__ins(fileState* workspace_file, int line, int position) {
	char** prev_line_keeper = malloc(sizeof(char*)*2);
	int startpos_fix = 0;
	
	int start_through_the_end = FALSE;

	//bool can_proceed = false;

	if(line < 0){
		free(prev_line_keeper);
		puts("You can't replace something before file's beginning... Exiting this command");
		return 99;
	}

	if(line<workspace_file->len) {
		if(position >= 0){
			if(position <= strlen(workspace_file->flc[line])) {
				startpos_fix = position;
			} else {
				puts("Start position is higher, than line length. Setting start position to line length\n");
				startpos_fix = strlen(workspace_file->flc[line]);
				start_through_the_end = TRUE;
			}
		} else {
			puts("You can't place substring somewhere before line. Exiting this command\n");
			free(prev_line_keeper);
			return 99; // 99 is just an error code. Why 99: because my finger was laying on '9' symbol on my kb
		}
	} else {
		printf("There is no line with this number... Exiting this command\n");
		free(prev_line_keeper);
		return 99;
	}

	int xi = 0;
	
	prev_line_keeper[0]=malloc(sizeof(char));
	prev_line_keeper[1]=malloc(sizeof(char));
	
	int new_len = 1; // used for both substring

	while(xi<startpos_fix) {
		prev_line_keeper[0] = realloc(prev_line_keeper[0], new_len*sizeof(char));
		prev_line_keeper[0][xi] = workspace_file->flc[line][xi];
		new_len++;
		xi++;
	}
	prev_line_keeper[0] = realloc(prev_line_keeper[0], new_len*sizeof(char));
	prev_line_keeper[0][xi] = '\0';

	int last_index = xi;
	xi = 0;
	new_len = 1;

	if(start_through_the_end!=TRUE){
		//int last_index = xi;
		//xi = 0;
		//new_len = 1;
		while(last_index+xi<strlen(workspace_file->flc[line])){ // well, now I see, that it would be a great idea... I mean adding int variable, which could keep result of last_index + xi... well, let it be.
			prev_line_keeper[1] = realloc(prev_line_keeper[1], sizeof(char)*new_len);
			prev_line_keeper[1][xi]=workspace_file->flc[line][xi+last_index];
			xi++;
			new_len++;
		}
	}
	prev_line_keeper[1] = realloc(prev_line_keeper[1], new_len*sizeof(char));
	prev_line_keeper[1][xi] = '\0';

	char input_thread_chars; 

	puts("Please, enter the substring, which you wanna insert");
	
	xi = 0;
	new_len = 1;
	char* appending_line=malloc(sizeof(char));

	while((input_thread_chars = getchar())!=EOF && input_thread_chars!='\n'){
		appending_line = realloc(appending_line, sizeof(char) * new_len);
		appending_line[xi] = input_thread_chars;
		new_len++;
		xi++;
		// YEAAAAAAAAAAH!!!!!! IT WORKS!!!!!!!!!!!!!!!!!!!!!!! FINALLY IT DOES NOT DROP IN MY FACE SOMETHING LIKE "Segmentation Fault (core dumped) 4132942187589432759874219847321847983217584375198435"
			       // ppl, who read this stuff, feel my happiness... I don't understand, what did I write in this file, but I like the fact that it still can work
	}
	putchar('\n');
	appending_line = realloc(appending_line, sizeof(char)*new_len);
	appending_line[xi] = '\0';


	xi = 0;
	new_len = 1;
	int zita = 0; // counter for second line

	char* final_line = malloc(sizeof(char));

	//concatenating
	while(prev_line_keeper[0][zita]) {
		final_line = realloc(final_line, new_len*sizeof(char));
		final_line[xi] = prev_line_keeper[0][zita];
		new_len++;
		xi++;
		zita++;
	}

	zita = 0;

	while(appending_line[zita]) {
		final_line = realloc(final_line, new_len*sizeof(char));
		final_line[xi] = appending_line[zita];
		zita++; xi++; new_len++;
	}

	zita = 0;

	while(prev_line_keeper[1][zita]) {
		final_line = realloc(final_line, new_len*sizeof(char));
		final_line[xi] = prev_line_keeper[1][zita];
		zita++; xi++; new_len++;
	}
	
	final_line = realloc(final_line, new_len*sizeof(char));
	final_line[xi] = '\0'; // IDK why do I forget about it any time I touch strings in C, but anyway I forget about it and tryna fix this stuff

	//printf("%s\n", final_line);

	free(workspace_file->flc[line]);
	workspace_file->flc[line] = final_line;

	/*
	while(xi < startpos_fix) {
		prev_line_keeper[0] = realloc(prev_line_keeper, sizeof(char*)*(xi+1));
		prev_line_keeper[0][xi]=workspace_file->flc[line][xi];
		xi++;
		
	}

	while(xi>=startpos_fix && xi < strlen(workspace_file->flc[line])) {
		break;
	}

	free(prev_line_keeper[0]); free(prev_line_keeper[1]); free(prev_line_keeper);
	*/

	free(prev_line_keeper[0]); free(prev_line_keeper[1]); free(prev_line_keeper); free(appending_line); //yeah, I was doing free(final_line), tho final_line and workspace_file->flc[line] are pointing to the same place (look 17 lines higher)... Ima genius!!!

	//printf("%d\n", line);
	//printf("%d\n", startpos_fix);
	//printf("%d\n", workspace_file->len);
}






uint8_t command__rm(fileState* workspace_file, int line, int from, int through) {
	//printf("there is nothing there!\n");
	char* new_line = malloc(sizeof(char));
	int xi = 0; //xi is a letter from Greek alphabet. Same to x. Xi is just currently used position
	int final_line_len = 1;
	int ref_line_len = strlen(workspace_file->flc[line]); // why did I add this stuff??? // well, it is needed for a small bugfix
	while(workspace_file->flc[line][xi] && xi < ref_line_len){
		if (xi<from || xi>through){
			++final_line_len;
			new_line = realloc(new_line, final_line_len*sizeof(char));
			new_line[final_line_len-2] = workspace_file->flc[line][xi];
		}
		xi++;
	} 
	new_line[final_line_len-1] = '\0';
	//puts(new_line);
	free(workspace_file->flc[line]);
	
	//printf("%d\n%d\n", sizeof(new_line), sizeof(workspace_file->flc[line]));
	workspace_file->flc[line]=new_line;
	//printf("result: %s\n", new_line);
	//printf("%d", strlen(workspace_file->flc[line]));
}






uint8_t command__w(fileState* workspace_file) {
	char* task = malloc(sizeof(char));
	char char_buffer;

	int len = 1;
	int xi = 0;
	int can_proceed = TRUE;
	
	puts("How you wanna write changes? write o, ae or aenti (overwrite, append, append with no tag input):");
	
	while ((char_buffer = getchar())!=EOF) {
		if(char_buffer == '\n') {
			char_buffer = '\0';
			can_proceed = FALSE;
		}
		task = realloc(task, sizeof(char)*len);
		task[xi] = char_buffer;
		len++;
		xi++;
		if(can_proceed != TRUE){
			break;
		}
	}

	if (strcmp(task, "o") == 0) {
		printf("Overwriting file...\n");
		FILE* file_out_stream = fopen(workspace_file->filename,"w");
		char* final_file = malloc(sizeof(char));
		
		int pos_x = 0, pos_y = 0;
		int appender_position = 0;
		while(pos_y<workspace_file->len){
			pos_x = 0;
			int size_of_current_line = strlen(workspace_file->flc[pos_y]);
			final_file = realloc(final_file, (strlen(final_file)+size_of_current_line+1)*sizeof(char));//+1 is for \n symbol
			while(workspace_file->flc[pos_y][pos_x]) {
				final_file[appender_position] = workspace_file->flc[pos_y][pos_x];
				appender_position++;
				pos_x++;
			}
			final_file[appender_position] = '\n';
			appender_position++;
			pos_y++;
		}

		final_file = realloc(final_file, (strlen(final_file)+1)*sizeof(char));
		//final_file[strlen(final_file)-1]= '\0';

		//printf("%s", final_file);
		
		

		int test = fputs(final_file, file_out_stream);
		if (test == EOF) {
			printf("Came face to face with a problem while file writting. Couldn't overwrite file");
		} else {
			printf("Success!\n");
		} // YES!!! IT WORKS!!!
		fclose(file_out_stream);
		free(final_file);
		return 0;
	} 

	if (strcmp(task, "ae") == 0) {
		printf("append tag is not ready at the moment. Try again in future versions, please\n");
	}

	if(strcmp(task, "aenti") == 0) {
		printf("append with no tag input is not ready at the moment. Try again in future versions, please\n");
	}

	//printf("%s\n", task);
	free(task);
}






uint8_t command__h() {
	printf("This list of commands shows small list of commands and some things, which these commands need, but doesn't show more info, than this, because else this list won't fit viewport on some machines. In order to see better help menu, write mh and visit github or start in-mh application\n\nlist:\n\nh - show this menu\n\nw - write file.\t{after writting this command and pressing enter} [o/ae/aenti - overwrite/append/append with no tag input]\n\nq - quit\n\nrm - remove area.\t{after writting this command and pressing enter} [line] [start position] [end position]\nrma - remove after.\t{after writting this command and pressing enter} [line] [start position]\n\nins - insert.\t{after pressing enter} [line] [position]\t{after pressing enter} [line, which you wanna insert]\nafl - add fracture line.\t {after writting this command and pressing enter} [line]\n");
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






int command__afl(fileState* workspace_file, int line_number) {
	if(line_number > workspace_file->len) {
		printf("line number is higher than file length + 1. Max possible number is: %d\n", workspace_file->len);
		return 1;
	}

	if(line_number < 0) {
		printf("You can't place something before file start. The least possible number is 0\n");
		return 1;
	}
	//printf("None");
	workspace_file->flc = realloc(workspace_file->flc, (workspace_file->len+1)*sizeof(char*));
	workspace_file->flc[workspace_file->len] = malloc(sizeof(char));
	for (int i = workspace_file->len; i > line_number; i--) {
		free(workspace_file->flc[i]);

		workspace_file->flc[i] = malloc(sizeof(char));
		int cur_l = 1;
		for(int j = 0; j<(strlen(workspace_file->flc[i-1])>=0?strlen(workspace_file->flc[i-1]):0); j++) {
			//printf("overwriting %d %d  ", i, j);
			workspace_file->flc[i] = realloc(workspace_file->flc[i], sizeof(char)*(j+1));
			workspace_file->flc[i][j] = workspace_file->flc[i-1][j];
			cur_l++;
		}

		//printf("%d\n", cur_l);

		workspace_file->flc[i] = realloc(workspace_file->flc[i], (cur_l)*sizeof(char)); //yup, I forgot that cur_l equals 1 when it is being defined and that means it will be 1 symbol 
		workspace_file->flc[i][cur_l-1] = '\0';
		//workspace_file->flc[i] = workspace_file->flc[i-1];
	}
	
	free(workspace_file->flc[line_number]);
	workspace_file->flc[line_number] = malloc(sizeof(char));
	workspace_file->flc[line_number][0] = '\0';
	/*
	printf("%d - %d - %d - %s", sizeof(char), sizeof('\0'), line_number, workspace_file->flc[line_number]);

	for (int i = 0; i <= workspace_file->len; i++) {
		printf("%d. %s\n", i, workspace_file->flc[i]);
	}*/

	workspace_file->len++;
	return 0;
	//printf("Added succesfully!\n");
}





int command__afln (fileState* workspace_file, int line, int count) {
	int accumulator=0;
	int state = 0;
	while(accumulator < count) {
		state = command__afl(workspace_file, line);
		if (state != 0) {
			printf("Stopped on `%d` itteration\n", accumulator+1);
			return 1;
		}
		accumulator++;
	}
	return 0;
}


int command__rml (fileState* workspace_file, int line) {
	return 0;
}


int command__rmln (fileState* workspace_file, int from_line, int through_line) {
	return 0;
}


uint8_t commandInput(fileState* workspace_file, char* input){
	uint8_t state = 0;
	if(strcmp(input, "q")==0){
		printf("Bye!\n");
		return QUIT_CODE;
	}

	if (strcmp(input, "w")==0) {
		command__w(workspace_file);
		state = 1;
	} 

	if (strcmp(input, "h")==0) {
		command__h();
		state = 1;
	}

	if (strcmp(input, "ins")==0) {
		int line_num, startpos;
		char fix;
		printf("Give positional arguments: line number, from position\n");
		printf("line number:\n");
		scanf("%d", &line_num);
		while((fix=getchar())!='\n' && fix != EOF);
		printf("start position:\n");
		scanf("%d", &startpos);
		while((fix=getchar())!='\n' && fix != EOF);

		command__ins(workspace_file, line_num, startpos);

		state = 1;
	}

	if (strcmp(input, "rma")==0){
		int line, from_pos;
		char ch;
		puts("Give positional arguments: line number and from which position you wanna remove text\n");
		puts("Line number: ");
		scanf("%d", &line);
		while ((ch=getchar())!='\n' && ch != EOF);
		puts("Position (remember, that 1st char in the line has 0th position, 2nd char has 1st position, 3rd has 2nd, 4th has 3rd, etc. Position means from which position line will be wiped): ");
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

	if(strcmp(input, "afl")==0) {
		int line_number;
		puts("Where do you want to add an empty line:");
		scanf("%d", &line_number);
		char fix;
		while((fix = getchar())!='\n' && fix !=EOF);
		int check = command__afl(workspace_file,line_number);
		if(check == 0) {
			printf("Added succesfully\n");
		} else if (check == 1) {
			printf("Something went wrong... please, try again\n");
		}
		state = 1;
	}

	if(strcmp(input, "afln")==0) {
		int line_number, count;
		char fix;
		puts("Where do you want to add empty lines:");
		scanf("%d", &line_number);
		while ((fix = getchar())!='\n'&&fix!=EOF);
		puts("How many lines do you want to add:");
		scanf("%d", &count);
		int result = command__afln(workspace_file, line_number, count);
		while((fix = getchar())!='\n' && fix != EOF);
		if(result == 0) {
			printf("Added successfully (%d lines)\n", count);
		} else {
			printf("Something went wrong... please, try again\n");
		}
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
	open_file_state->len = 0;
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
			workspace_file->flc[line] = realloc(workspace_file->flc[line], (pos+2)*sizeof(char));
			workspace_file->flc[line][pos] = fileInputBuffer;
			//printf("reallocated (only char)!\n");
			++pos;
			//++multiplier;
		} else {
			workspace_file->len+=1;
			// well, why do I reallocate only if this stuff is empty? I have got some questions: maybe, it's better to place a boolean variable, which could save data about \n existence and then check if the char is not EOF so it will just reallocate... Hard to say
			//printf("%d", (line+1)*sizeof(char*));
			workspace_file->flc[line]=realloc(workspace_file->flc[line], (pos+2)*sizeof(char));
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
	while(chk<workspace_file->len) {
		//printf("%s\t\t", workspace_file->flc[chk]);
		free(workspace_file->flc[chk]);
		//printf("Cleaning memory %d\n", chk);
		chk++;
	}
	//free(workspace_file->flc);
	//printf("%d\n", sizeof(workspace_file->flc));
	//printf("Cleaning memory, but fully\n");
}
