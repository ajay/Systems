/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * mallocEnh.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mallocEnh.h"

#define MEMSIZE 5000
static void* Memory[MEMSIZE];
static MemEntry * root = 0;
static MemEntry * last = 0;
static int index = 0;

void removeFromMemory(MemEntry *data)
{
	int j;
	for(j=0; j<index; j++)
	{
		if(data == Memory[j])
		{
			Memory[j] = NULL;
			return;
		}
	}
}

void *myMalloc(unsigned int size, char * file, int l)
{
	static bool initialized = false;
    static MemEntry *root;
    MemEntry *pointer;
    MemEntry *next;

    if (!initialized)
    {
        root = (MemEntry *)Memory;
        root->prev = root->next = 0;
        root->size = MEMSIZE - sizeof(MemEntry);
        root->isFree = 1;
        initialized = true;
    }

    pointer = root;

    while (pointer != 0)
    {
        if (pointer->size < size)
        {
            pointer = pointer->next;
        }
        else if (!pointer->isFree)
        {
            pointer = pointer->next;
        }
        else if (pointer->size < (size + sizeof(MemEntry)))
        {
            pointer->isFree = 0;
            removeFromMemory(pointer);
            return (char *)pointer + sizeof(MemEntry);
        }
        else
        {
            next = (MemEntry *)((char *)pointer + sizeof(MemEntry) + size);
            next->prev = pointer;
            next->next = pointer->next;
            if(pointer->next != 0)
            {
                pointer->next->prev = next;
            }
            pointer->next = next;
            next->size = pointer->size - sizeof(MemEntry) - size;
            next->isFree = 1;
            pointer->size = size;
            pointer->isFree = 0;
            last = (pointer == last) ? next : last;
            removeFromMemory(pointer);
            return (char *)pointer + sizeof(MemEntry);
        }
    }

    pointer = (MemEntry *)sbrk(sizeof(MemEntry) + size);
    if (pointer == (void*)-1)
    {
        return 0;
    }
    else if (last == 0)
    {
        printf("BKR making first chunk size %d\n", size);
        pointer->prev = 0;
        pointer->next = 0;
        pointer->size = size;
        pointer->isFree = 0;
        root = last = pointer;
        return (char *)pointer + sizeof(MemEntry);
    }
    else
    {
        printf( "BKR making another chunk size %d\n", size);
        pointer->prev = last;
        pointer->next = last->next;
        pointer->size = size;
        pointer->isFree = 0;
        last->next = pointer;
        last = pointer;
        return (char *)pointer + sizeof(MemEntry);
    }

    return 0;
}

void myFree(void *pointer, char* file, int l)
{
    MemEntry *ptr;
    MemEntry *pred;
    MemEntry *next;

    ptr = (MemEntry *)((char *)pointer - sizeof(MemEntry));

    MemEntry *temp = root;

    while (root != 0)
    {
		if (ptr == root)
		{
            break;
        }
        root = root->next;
        if(root == 0)
		{
			printf("\e[1;31mERROR: The parameter passed to free() has not been malloc'd, or has been free'd already.\n\e[0m");
            root = temp;
            return;
        }
    }

    int j;
    for (j=0; j<index; j++)
    {
    	if (ptr == Memory[j])
		{
            printf("\e[1;31mERROR: The parameter passed to free() has been free'd already.\n\e[0m");
            return;
        }
    }

    root = temp;

    if ((pred = ptr->prev) != 0 && pred->isFree)
    {
        pred->size += sizeof(MemEntry) + ptr->size;

        pred->next = ptr->next;
        ptr->isFree = 1;
        pred->next = ptr->next;
        if(ptr->next != 0)
        {
			ptr->next->prev = pred;
        }
 //       printf( "BKR freeing block %#x merging with predecessor new size is %d.\n", p, pred->size );
    }
    else
    {
//        printf( "BKR freeing block %#x.\n", p );
        Memory[index++] = ptr;
        ptr->isFree = 1;
        pred = ptr;
    }
    if ( (next = ptr->next) != 0 && next->isFree )
    {
        pred->size += sizeof(MemEntry) + next->size;
        pred->next = next->next;
        pred->isFree = 1;
        if(next->next != 0)
        {
            next->next->prev=pred;
        }
        Memory[index++] = ptr;
 //       printf( "BKR freeing block %#x merging with nextessor new size is %d.\n", p, pred->size );
    }
}