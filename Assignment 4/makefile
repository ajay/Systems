CC = gcc
CFLAGS = -g -Wall -pedantic
COMPILE = $(CC) $(CFLAGS)
PROGRAM = indexer

all: $(PROGRAM)

simpleTokenizer.o: simpleTokenizer.c simpleTokenizer.h
	$(COMPILE) -c $<

trieTree.o: trieTree.c trieTree.h
	$(COMPILE) -c $<

indexer.o: indexer.c indexer.h
	$(COMPILE) -c $<

$(PROGRAM): simpleTokenizer.o trieTree.o indexer.o
	$(COMPILE) -o $@ $^

clean:
	rm -rfv *.o $(PROGRAM)