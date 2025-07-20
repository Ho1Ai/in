CC = gcc

FINAL = build/in
SOURCE = src/main.c src/editor/editor.c

CFLAGS = $(SOURCE) -o $(FINAL) # not -Wall, because I don't return some things somewhere in non-void funcs

$(FINAL):$(SOURCE)
	$(CC) $(CFLAGS)

build_in-mh:
	fpc ./src/in-mh.pas
	cp ./src/in-mh ./build/
	rm ./src/in-mh

build_full: #did everything in this stuff, cuz I need makefile in in-editor package. For future stuff
	$(CC) $(CFLAGS)
	fpc ./src/in-mh.pas
	cp ./src/in-mh ./build/
	rm ./src/in-mh

