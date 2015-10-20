/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * mallocEnh.h for mallocEnh.c
 */

#ifndef MALLOC_H
#define MALLOC_H

#define malloc(x) myMalloc(x, __FILE__, __LINE__)
#define free(x) myFree(x, __FILE__, __LINE__)

#include <stdbool.h>

struct MemEntry
{
	struct MemEntry *next;
	struct MemEntry *prev;
	unsigned int size;
	bool isFree;
	bool isMemEntry;
	char *file;
	unsigned int line; 
};

typedef struct MemEntry MemEntry;

void *myMalloc(unsigned int size, char* file, int l);
void myFree(void *Pointer, char* file, int l);

#endif