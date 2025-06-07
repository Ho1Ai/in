CC = gcc

FINAL = build/in
SOURCE = src/main.c src/editor/editor.c

CFLAGS = $(SOURCE) -o $(FINAL)

$(FINAL):$(SOURCE)
	$(CC) $(CFLAGS)
