/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * mallocEnh.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "mallocEnh.h"

#define MEMSIZE 5000
static void* Memory[MEMSIZE];

static struct MemEntry * root = 0;
static struct MemEntry * last = 0;
// void *arr[5000];
static int i = 0;

void removeFromMemory(struct MemEntry *p)
{
	int j;
	for(j=0;j<i;j++)
	{
		if(p == Memory[j])
		{
			Memory[j]= NULL;
			return;
		}
	}
}

void *myMalloc(unsigned int size, char * file, int l)
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
        if ( p->size < size )
        {
            p = p->succ;                 							// too small
        }
        else if ( !p->isFree )
        {
            p = p->succ;                 							// in use
        }
        else if ( p->size < (size + sizeof(struct MemEntry)) )
        {
            p->isFree = 0;                   						// too small to chop up
            removeFromMemory(p);
            return (char *)p + sizeof(struct MemEntry);
        }
        else
        {
            succ = (struct MemEntry *)((char *)p + sizeof(struct MemEntry) + size);
            succ->prev = p;
            succ->succ = p->succ;
            if(p->succ != 0)
            {
                p->succ->prev = succ;
            }
            p->succ = succ;
            succ->size = p->size - sizeof(struct MemEntry) - size;
            succ->isFree = 1;
            p->size = size;
            p->isFree = 0;
            last = (p == last) ? succ : last;
            removeFromMemory(p);
            return (char *)p + sizeof(struct MemEntry);
        }
    } while (p != 0);

    if ( (p = (struct MemEntry *)sbrk( sizeof(struct MemEntry) + size )) == (void *)-1 )
    {
        return 0;
    }
    else if ( last == 0 )               							// first block created
    {
        printf( "BKR making first chunk size %d\n", size );
        p->prev = 0;
        p->succ = 0;
        p->size = size;
        p->isFree = 0;
        root = last = p;
        return (char *)p + sizeof(struct MemEntry);
    }
    else                        									// other blocks appended
    {
        printf( "BKR making another chunk size %d\n", size );
        p->prev = last;
        p->succ = last->succ;
        p->size = size;
        p->isFree = 0;
        last->succ = p;
        last = p;
        return (char *)p + sizeof(struct MemEntry);
    }

    return 0;
}

void myFree(void *p, char* file, int l)
{
    struct MemEntry *       ptr;
    struct MemEntry *       pred;
    struct MemEntry *       succ;
     
    ptr = (struct MemEntry *)((char *)p - sizeof(struct MemEntry));
     
    struct MemEntry *temp = root;
     
    while (root != 0) {
        if (ptr == root) {
            break;
        }
        root = root->succ;
        if(root == 0){
            printf("<ERROR>: Has not been malloc or freed already\n");
            root = temp;
            return;
        }
    }
     
    int j;
    for (j = 0; j < i; j++) {
        if (ptr == Memory[j]) {
            printf("<ERROR>: Has already been freed\n");
            return;
        }
    }

    root = temp;

    if ( (pred = ptr->prev) != 0 && pred->isFree )
    {
        pred->size += sizeof(struct MemEntry) + ptr->size;    // merge with predecessor
         
        pred->succ = ptr->succ;
        //begin added
        ptr->isFree=1;
        pred->succ = ptr->succ;
        if(ptr->succ != 0)
            ptr->succ->prev = pred;
        //end added
 //       printf( "BKR freeing block %#x merging with predecessor new size is %d.\n", p, pred->size );
    }
    else
    {
//        printf( "BKR freeing block %#x.\n", p );
        Memory[i++] = ptr;
        ptr->isFree = 1;
        pred = ptr;
    }
    if ( (succ = ptr->succ) != 0 && succ->isFree )
    {
        pred->size += sizeof(struct MemEntry) + succ->size;   // merge with successor
        pred->succ = succ->succ;
        //begin added
        pred->isFree = 1;
         
        if(succ->succ != 0)
            succ->succ->prev=pred;
        //end added
        Memory[i++] = ptr;
 //       printf( "BKR freeing block %#x merging with successor new size is %d.\n", p, pred->size );
    }
}