CC = gcc
CFLAGS = -g 
COMPILE = $(CC) $(CFLAGS)
TARGET = main.c

myMalloc: $(TARGET) mallocEnh.o
	$(COMPILE) -o myMalloc $(TARGET) mallocEnh.o

mallocEnh.o: mallocEnh.c mallocEnh.h
	$(COMPILE) -c mallocEnh.c

clean:
	rm -rfv myMalloc mallocEnh.o