/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * mallocEnh.h for mallocEnh.c
 */

#ifndef MALLOC_H
#define MALLOC_H

#define malloc(x) myMalloc(x, __FILE__, __LINE__)
#define free(x) myFree(x, __FILE__, __LINE__)

struct MemEntry
{
	unsigned int size;
	unsigned int isFree;
	struct MemEntry *next;
	struct MemEntry *prev;
};

typedef struct MemEntry MemEntry;

void *myMalloc(unsigned int size, char* file, int l);
void myFree(void *Pointer, char* file, int l);

#endif