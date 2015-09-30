CC = gcc

CFLAGS = -Wall -g

all: sorted-list.c sorted-list.h main.c
	clear
	$(CC) $(CFLAGS) -c sorted-list.c
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o main main.o sorted-list.o
	@echo "./main\n"
	@./main
	@echo

clean:
	rm -f main main.o sorted-list.o