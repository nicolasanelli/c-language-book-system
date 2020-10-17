CC = gcc
CCFLAGS = -Wall

main: 
	$(CC) $(CCFLAGS) booksystem.c layout.c database.c -o BookSystem

clean:
	rm BookSystem 
