CC = gcc
CFLAGS = -W
TARGET = wordbook_exe
OBJECTS = WordBook.o WordTree.o

$(TARGET) : $(OBJECTS)
		$(CC) $(CFLAGS) -o $@ $^

WordBook.o : WordBook.c
		$(CC) $(CFLAGS) -c -o WordBook.o WordBook.c

WordTree.o : WordTree.c
		$(CC) $(CFLAGS) -c -o WordTree.o WordTree.c

clean : 
		rm $(OBJECTS)
