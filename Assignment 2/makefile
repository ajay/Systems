CC = gcc
CFLAGS = -Wall -g
COMPILE = $(CC) $(CFLAGS)

sl: libsl.a main.c
	$(COMPILE) -o sl main.c libsl.a

libsl.a: sorted-list.o
	ar rv libsl.a sorted-list.o

sorted-list.o: sorted-list.c sorted-list.h
	$(COMPILE) -c sorted-list.c

clean:
	rm -rfv sl sorted-list.o libsl.a