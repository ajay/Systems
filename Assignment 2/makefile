CC = gcc

CFLAGS = -Wall -g

all: sorted-list.c sorted-list.h main.c
	clear
	$(CC) $(CFLAGS) -c sorted-list.c
	$(CC) $(CFLAGS) -o main main.c
	@echo "./main\n"
	@./main
	@echo

clean:
	rm -f main sorted-list.o