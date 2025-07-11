CC = gcc

FINAL = build/in
SOURCE = src/main.c src/editor/editor.c

CFLAGS = $(SOURCE) -o $(FINAL) # not -Wall, because I don't return some things somewhere in non-void funcs

$(FINAL):$(SOURCE)
	$(CC) $(CFLAGS)
