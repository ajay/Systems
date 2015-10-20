/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * mallocEnh.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mallocEnh.h"

#define MemEntrySize sizeof(MemEntry)
#define reset   "\x1b[0m"
#define red     "\x1b[31m"
#define green   "\x1b[32m"

static MemEntry * root = 0;
static MemEntry * last = 0;
static int index = 0;
static int TOTALMEMORY = 0;

void leak()
{
	MemEntry *current = root;
	while (current != 0)
	{
		if(current->isFree == false)
		{
			printf(red "ERROR: There was a memory leak. An item on line " green "%d" red " of " green "%s" red " may not have been free'd.\n" reset, current->line, current->file);
		}
		current = current->next;
	}
}

void* myMalloc(unsigned int bytes, char *file, int line)
{
	atexit(leak);

	if (bytes == 0)
	{
		printf(red "ERROR: Can not allocate " green "%d" red " bytes. An item on line " green "%d" red " of " green "%s" red " caused this error.\n" reset, bytes, line, file);
		return NULL;
	}

	MemEntry *block = 0;
	MemEntry *current;
	MemEntry *next;
	current = root;

	while (current != 0)
	{
		if (current->size < bytes)
		{
			current = current->next;
		}
	    else if (!current->isFree)
	    {
	    	current = current->next;
	    }
	    else if (block->size < current->size) 
	    {
			block = current;
			current = current->next;
	    }
	    else
	    {
			current = current->next;
	    }
	}

	if(block != 0)
	{
		if (block->size < (bytes + 2*MemEntrySize))
		{
			block->isFree = false;
			return block+1;
		}
		else
		{
			next = (MemEntry *)((char*)block + MemEntrySize + bytes);
			next->prev = block;
			next->next = block->next;
			if (block->next != 0)
			{
				block->next->prev = next;
			}
			block->next = next;
			next->size = block->size - MemEntrySize - bytes;
			next->isFree = true;
			next->isMemEntry = true;
			block->size = bytes;
			block->isFree = false;
			block->isMemEntry = true;
			block->file = file;
			block->line = line;
			return block+1;
	    }
	}

	current = (MemEntry *)sbrk(TOTALMEMORY += bytes + MemEntrySize);
	if (current == (void*)-1)
	{
		printf(red "ERROR: sbrk() was unable to provide memory for malloc(). An item on line " green "%d" red " of " green "%s" red " may have caused this.\n", line, file);
		TOTALMEMORY -= bytes + MemEntrySize;
		return 0;
	}

	else if (last == 0)
	{
		current->next = current->prev = 0;
		current->size = bytes;
		current->isFree = false;
		current->isMemEntry = true;
		root = last = current;
		current->file = file;
		current->line = line;
		return current+1;
	}

	else
	{
		current->prev = last;
		current->next = last->next;
		current->size = bytes;
		current->isFree = false;
		current->isMemEntry = true;
		last->next = current;
		last = current;
		current->file = file;
		current->line = line;
		return current+1;
	}
  
	printf(red "ERROR: Malloc failed. An item on line " green "%d" red " of " green "%s" red " may have caused this.\n", line, file);
	return 0;
}

void myFree(void *pointerToFree, char* file, int line)
{
	if(pointerToFree == NULL)
	{
		printf(red "ERROR: free() cannot free a 'NULL' pointer. An item on line " green "%d" red " of " green "%s" red " may have caused this.\n", line, file);
		return;
	}

	MemEntry *current;
	MemEntry *pred;
	MemEntry *next;
	current = (MemEntry *)pointerToFree-1;

	if(!(current <= TOTALMEMORY + root && current >= root))
	{
		printf(red "ERROR: free() cannot free a pointer that was not dynamically allocated. An item on line " green "%d" red " of " green "%s" red " may have caused this.\n", line, file);
		return;
	}

	if(current->isMemEntry != true)
	{
		printf(red "ERROR: free() cannot free a pointer that was not returned from malloc. An item on line " green "%d" red " of " green "%s" red " may have caused this.\n", line, file);
		return;
	}

	if(current->isFree == true)
	{
		printf(red "ERROR: free() cannot free a pointer that is unallocated. An item on line " green "%d" red " of " green "%s" red " may have caused this.\n", line, file);
		return;
	}

	if((pred = current->prev)!=0 && pred->isFree == true)
	{
		pred->size += current->size + MemEntrySize;
		pred->next = current->next;
		if(current->next!=0)
		{
			current->next->prev = pred;
		}
	}

	else
	{
		current->isFree = true;
		pred = current;
	}

	if((next = pred->next) != 0 && next->isFree == true)
	{
		pred->size += next->size + MemEntrySize;
		pred->next = next->next;
		if(next->next != 0)
		{
			next->next->prev = pred;
		}
	}

	if(pred->next == 0)
	{
		if(pred->prev != 0)
		{
			pred->prev->next = 0;
			last = pred->prev;
			TOTALMEMORY -= pred->size + MemEntrySize;
			sbrk(-(pred->size + MemEntrySize));
		}
	    else
		{
			root = 0;
			last = 0;
			TOTALMEMORY = 0;
			sbrk(-(pred->size + MemEntrySize));
	    }
	}
}