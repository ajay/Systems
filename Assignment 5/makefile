CC = gcc
CFLAGS = -g -Wall -pedantic
COMPILE = $(CC) $(CFLAGS)
PROGRAMS = client server

all: $(PROGRAMS)

server: server.c
	$(COMPILE) -o $@ $<

client: client.c
	$(COMPILE) -o $@ $<

clean:
	rm -rfv *.o $(PROGRAMS)