# IN text editor
In (in <- insert) is a small and lightweight text editor, which I wrote just to write cfg files and something like that while Linux Installation

2025/06/13 update: it will use next commands:  
`out` - output all lines. After entering this command and pressing enter application will ask you for line numbers. In order to output full file you should write `-1 -1`.  
`rma` - remove after (only for lines. I mean "remove after position in chosen line"). After entering this command and pressing enter application will ask you for line number and position from which you wanna remove (from this position through the end of line)  
`ins` - insert. Insert something. Asks for two things: line and position. Then it will ask you what you wanna add  
`rm` - remove. removes area. Requires three things: line, start position, end position  
`w` - write. Write changes to file  
`h` - help. Output list of commands  
If you are trying to enter the command that does not exist, application will output `not a command. Write "h" to show list of supported commands`  
this list is not ready yet, but it is that minimum, which this application needs  
(P.S. inspired by ed ;) )  
(P.P.S. in more help (in-mh) is written in Pascal. Imho, not bad language, btw)  

## Installation Guide (added on 2025/07/14 (early morning)):  
The package has been added to AUR, so it may be installed using `yay -S in-editor`, but if you wanna install it by yourself, you can follow next steps:  
1. Clone git repository - `git clone https://github.com/Ho1Ai/in`  
P.S.: instead of next steps you can start install.sh (install in) and install-mh.sh (install in-mh). These files needs `sudo`, so, if you use `doas` instead or use `su` (in order to do everything as root), you had better follow next steps (or, if you use `doas`, write `doas cp ...` instead of `sudo cp ...` in shell scripts)
2. Go to the cloned dir and find build files. Then use next: `cd in/build`  
3. Use next command: `sudo cp ./in /usr/local/bin/`. This command will copy in text editor to `/usr/local/bin/`, so you don't need to use `./in <filename>` instead of `in <filename>`
4. (*optional*) You can also copy `in-mh`. Then use next command: `sudo cp ./in-mh /usr/local/bin/`. It is needed to get more info about command (mh means more help, so it is the reason why it is called like that).

