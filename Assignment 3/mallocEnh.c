/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * mallocEnh.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "mallocEnh.h"

#define MEMSIZE 5000
static char Memory[MEMSIZE];

void *myMalloc(unsigned int size, char * file, int l)
{
    static int initialized = 0;
    static struct MemEntry *root;
    struct MemEntry *p;
    struct MemEntry *next;

    if (!initialized)
    {
        root = (struct MemEntry *)Memory;
        root->prev = root->next = 0;
        root->size = MEMSIZE - sizeof(struct MemEntry);
        root->isFree = 1;
        initialized = 1;
    }

    p = root;

    do
    {
        if (p->size < size)
        {
            p = p->next;            // too small
        }
        else if (!p->isFree)
        {
            p = p->next;            // in use
        }
        else if (p->size < (size + sizeof(struct MemEntry)))
        {
            p->isFree = 0;
            return (char *)p + sizeof(struct MemEntry);
        }
        else
        {
            next = (struct MemEntry*) ((char *)p + sizeof(struct MemEntry) + size);
            next->next = p->next;
            if(p->next !=0)
                p->next->prev = next;
            p->next = next;
            next->size = p->size - sizeof(struct MemEntry) - size;
            next->isFree = 1;
            p->size = size;
            p->isFree = 0;
            return (char *)p + sizeof(struct MemEntry);
        }
    } while (p != 0);
    return 0;
}

void myFree(void *p, char* file, int l)
{
    struct MemEntry *ptr;
    struct MemEntry *pred;
    struct MemEntry *next;
    ptr = (struct MemEntry*) ((char *)p - sizeof(struct MemEntry));
    if ((pred = ptr->prev ) !=0 && pred->isFree)
    {
        pred->size += sizeof(struct MemEntry) + ptr->size; //merge with predecessor
        pred->next = ptr->next;
        if (ptr->next != 0)
            ptr->next->prev = pred;
    }
    else
    {
        ptr->isFree = 1;
        pred = ptr;
    }
    if ((next = ptr->next) !=0 && next->isFree)
    {
        pred->size += sizeof(struct MemEntry) + next->size;     // merge with next
        pred->next = next->next;
        if (next->next !=0)
            next->next->prev = pred;
    }
}