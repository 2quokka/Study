CC = gcc
CFLAGS = -W
TARGET = maze.exe
OBJECTS = listgraph.o maze.o

$(TARGET) : $(OBJECTS)
		$(CC) $(CFLAGS) -o $@ $^

listgraph.o : listgraph.c linkedlist.c
		$(CC) $(CFLAGS) -c -o listgraph.o listgraph.c linkedlist.c

maze.o : maze.c
		$(CC) $(CFLAGS) -c -o maze.o maze.c

clean : 
		rm $(OBJECTS)
