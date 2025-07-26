var pages_content: array[0..25] of WideString;
var page_number: integer;
var continuation: boolean;
begin
	continuation:=true;
	page_number:=0;
	writeln('in order to close, write -1');
	writeln('in order to switch between pages, use numbers between 1 and 11 (use 0 to show this page)');
	writeln('it is just a small guide. Somewhere you can find some changes in commands outputs, but I did not change main idea');
	writeln('since 01050b.t (or 01041b.4p.t if somewhere mentioned) some commands can get arguments from first input. So now you can write "out -1 -1" instead of "out <enter> -1 <enter> -1". You can also write using old way (may be marked as "legacy"), but some aspects in commands input have been reworked');
	pages_content[0]:='content ({list position}. page - command):'+#10#13+'1. q - 1'+#10#13+'2. h - 2'+#10#13+'3. c - 3'+#10#13+'4. w - 4'+#10#13+'5. rm - 5'+#10#13+'6. rma - 6'+#10#13+'7. out - 7'+#10#13+'8. ins - 8'+#13#10+'9. draw - 9'+#13#10+'10. afl - 10'+#13#10+'11. afln - 11'+#13#10+'12. rml - 12'+#13#10+'13. rmln - 13'+#13#10+'14. cfn - 14'+#13#10+'15. mktab - 15';
	pages_content[1]:='q <=> quit'+#13#10+'Does not require any arguments. Can only quit in text editor'+#13#10#10+'{e.g.:}'+#10+'> q'+#10+'Bye!';
	pages_content[2]:='h <=> help'+#13#10+'Does not require any arguments. Can only show help message.'+#10+'Also there is "mh" command, but it does not do anything. It only says, that there is also an application, called in-mh';
	pages_content[3]:='c <=> clean'+#13#10+'Does not require any arguments. Can only clean the screen. Uses system("clear")';
	pages_content[4]:='w <=> write'+#13#10+'Since 00008a requires one positional argument: write type. At the moment the only possible type is "o" (overwrite)';
	pages_content[5]:='rm <=> remove (area)'+#13#10+'Requires following arguments:'+#13#10+'[line number] [start position] [last position]'+#13#10#10+'{e.g.:}'+#10+'> rm'+#10+'Give positional arguments: line number, start position, last position'+#10+'> 10 10 20'+#10+'Done';
	pages_content[6]:='rm <=> remove after'+#13#10+'Requires following arguments:'+#13#10+'[line number] [from position]'+#13#10#10+'{e.g.:}'+#10+'> rma'+#10+'Give positional arguments: line number, from position'+#10+'> 10'+#10+'from position:'+#10+'> 10'+#10+'Done';
	pages_content[7]:='out <=> output'+#13#10+'Requires following arguments:'+#13#10+'[start line number] [end line number]'+#13#10#10+'{e.g.:}'+#10+'> out'+#10+'Give positional arguments:'+#10+'start line number:'+#10+'> 10'+#10+'end line number:'+#10+'> 11'+#10#10+'10.  Lorem Ipsum'+#10+'11.  Lorem ipsum dolor sit amet <...>';
	pages_content[8]:='ins <=> insert'+#13#10+'Requires following arguments (splitted in 2 steps):'+#13#10+'1. [line number] [from position]'+#10+'2. [text to insert]'+#10#10+'{e.g.:}'+#10+'> ins'+#10+'Give positional arguments: line number, from position'+#10+'> 10 10'+#10+'Write text you wanna insert (max buffer size is 1024)'+#10+'> Lorem ipsum dolor sit amet...'+#10#10+'Note: there is no buffer size, btw. It has been added when I was making this in-mh file';
	pages_content[9]:='draw (indev command)'+#13#10+'Outputs full file content. Does not need any arguments'+#10+'Example:'+#10#10+'> draw'+#10+'0. Some'+#10+'1. text'+#10+'2. is'+#10+'3. here'+#10+'4. No matter what text btw';
	pages_content[10]:='afl <=> add fracture line' + #13#10 + 'Requires line number, where you wanna create empty line. Creates empty line'+#10+'Example:'+#10+'> afl'+#10+'Where do you want to add an empty line:'+#10#10+'2 {e.g.}'+#10+'Added succesfully!';
	pages_content[11]:='afln <=> add fracture lines (number of lines)'+#13#10+'Requires line number and number of empty lines. Same to afl (look at the previous page (afl))';
	pages_content[12]:='rml <=> remove line'+#13#10+'Requires number of line, which you wanna remove'+#10+'Example:'+#10+'> rml'+#10+'Which line do you wanna remove:'+#10+'2 {e.g.}'+#10+'Success! (or an error if you are tryna remove line with number, which one is less than 0 or greater than number of last line)';
	pages_content[13]:='rmln <=> remove lines (number of lines)'+#13#10+'Requires line number and how many lines you wanna remove (it uses a small counter inside). Same to rml (check rml page), but also requires number, which shows, how many lines do you wanna remove';
	pages_content[14]:='cfn <=> change file name'+#13#10+'Requires new file name'+#10+'Example:'+#10+'> cfn'+#10+'What file name do you wanna set:'+#10+'new_file.totmb'+#10#10+'{in case file with this file name already exist, it will ask you if you are sure you wanna set this file name. If you are sure, write "y" or "Y", else write anything else (or just press enter)}';
	pages_content[15]:='mktab <=> make tab'+#13#10+'Adds tabs in the beggining of the line if you are trying to insert something into an empty line'+#10+'Requires only task: + (in order to increase count of tabs) or - (in order to decrease count of tabs)';
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
