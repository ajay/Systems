/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * mallocEnh.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "mallocEnh.h"

#define MEMSIZE 5000

static char Memory[MEMSIZE];

void *myMalloc(unsigned int size, char* file, int l)
{
    static int initialized = 0;
    static struct MemEntry *root;
    struct MemEntry *p;
    struct MemEntry *succ;

    if (!initialized)
    {
        root = (struct MemEntry *)Memory;
        root->prev = root->succ = 0;
        root->size = MEMSIZE - sizeof(struct MemEntry);
        root->isFree = 1;
        initialized = 1;
    }

    p = root;

    do
    {
        if (p->size < size)
        {
            p = p->succ;            // too small
        }
        else if (!p->isFree)
        {
            p = p->succ;            // in use
        }
        else if (p->size < (size + sizeof(struct MemEntry)))
        {
            p->isFree = 0;
            return (char *)p + sizeof(struct MemEntry);
        }
        else
        {
            succ = (struct MemEntry*) ((char *)p + sizeof(struct MemEntry) + size);
            succ->succ = p->succ;
            if(p->succ !=0)
                p->succ->prev = succ;
            p->succ = succ;
            succ->size = p->size - sizeof(struct MemEntry) - size;
            succ->isFree = 1;
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
    struct MemEntry *succ;
    ptr = (struct MemEntry*) ((char *)p - sizeof(struct MemEntry));
    if ((pred = ptr->prev ) !=0 && pred->isFree)
    {
        pred->size += sizeof(struct MemEntry) + ptr->size; //merge with predecessor
        pred->succ = ptr->succ;
        if (ptr->succ != 0)
            ptr->succ->prev = pred;
    }
    else
    {
        ptr->isFree = 1;
        pred = ptr;
    }
    if ((succ = ptr->succ) !=0 && succ->isFree)
    {
        pred->size += sizeof(struct MemEntry) + succ->size;     // merge with succ
        pred->succ = succ->succ;
        if (succ->succ !=0)
            succ->succ->prev = pred;
    }
}