var pages_content: array[0..25] of WideString;
var page_number: integer;
var continuation: boolean;
begin
	continuation:=true;
	page_number:=0;
	writeln('in order to close, write -1');
	writeln('in order to switch between pages, use numbers between 1 and 8 (use 0 to show this page)');
	
	pages_content[0]:='content ({list position}. page - command):'+#10#13+'1. q - 1'+#10#13+'2. h - 2'+#10#13+'3. c - 3'+#10#13+'4. w - 4'+#10#13+'5. rm - 5'+#10#13+'6. rma - 6'+#10#13+'7. out - 7'+#10#13+'8. ins - 8'+#13#10+'9. draw - 9'+#13#10+'10. afl - 10'+#13#10+'11. afln - 11';
	pages_content[1]:='q <=> quit'+#13#10+'Does not require any arguments. Can only quit in text editor'+#13#10#10+'{e.g.:}'+#10+'> q'+#10+'Bye!';
	pages_content[2]:='h <=> help'+#13#10+'Does not require any arguments. Can only show help message';
	pages_content[3]:='c <=> clean'+#13#10+'Does not require any arguments. Can only clean the screen. Uses system("clear")';
	pages_content[4]:='w <=> write'+#13#10+'Does not require any arguments. Writes opened file';
	pages_content[5]:='rm <=> remove (area)'+#13#10+'Requires following arguments:'+#13#10+'[line number] [start position] [last position]'+#13#10#10+'{e.g.:}'+#10+'> rm'+#10+'Give positional arguments: line number, start position, last position'+#10+'> 10 10 20'+#10+'Done';
	pages_content[6]:='rm <=> remove after'+#13#10+'Requires following arguments:'+#13#10+'[line number] [from position]'+#13#10#10+'{e.g.:}'+#10+'> rma'+#10+'Give positional arguments: line number, from position'+#10+'> 10 10'+#10+'Done';
	pages_content[7]:='out <=> output'+#13#10+'Requires following arguments:'+#13#10+'[start line number] [end line number]'+#13#10#10+'{e.g.:}'+#10+'> out'+#10+'Give positional arguments: start line number, end line number'+#10+'> 10 11'+#10+'==___---___=='+#10+'Lorem Ipsum'+#10+'Lorem ipsum dolor sit amet <...>';
	pages_content[8]:='ins <=> insert'+#13#10+'Requires following arguments (splitted in 2 steps):'+#13#10+'1. [line number] [from position]'+#10+'2. [text to insert]'+#10#10+'{e.g.:}'+#10+'> ins'+#10+'Give positional arguments: line number, from position'+#10+'> 10 10'+#10+'Write text you wanna insert (max buffer size is 1024)'+#10+'> Lorem ipsum dolor sit amet...'+#10#10+'Note: there is no buffer size, btw. It has been added when I was making this in-mh file';
	pages_content[9]:='draw (indev command)'+#13#10+'Outputs full file content. Does not need any arguments'+#10+'Example:'+#10#10+'> draw'+#10+'0. Some'+#10+'1. text'+#10+'2. is'+#10+'3. here'+#10+'4. No matter what text btw';
	pages_content[10]:='afl <=> add fracture line' + #13#10 + 'Requires line number, where you wanna create empty line. Creates empty line'+#10+'Example:'+#10+'> afl'+#10+'Where do you want to add an empty line:'+#10#10+'2 {e.g.}'+#10+'Added succesfully!';
	pages_content[11]:='afln <=> add fracture lines (number of lines)'+#13#10+'Requires line number and number of empty lines. Same to afl (look at the previous page (afl))';
	writeln('page: ', page_number);
	writeln(pages_content[0]);
	writeln(#13#10#10);
	while continuation do begin
		//writeln('page: ', page_number);
		//writeln(pages_content[page_number]);
		writeln(#13#10#10);
		readln(page_number);
		if page_number=-1 then continuation:=false
		else begin 
			writeln('page: ', page_number); 
			writeln(pages_content[page_number]);
			writeln(#13#10#10#10); 
		end;
	end;
end.
