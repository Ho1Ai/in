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
