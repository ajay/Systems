/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * sorted-list.c
 */

#include <stdio.h>
#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
	printf("Test123\n");
	if (cf == NULL)
	{
		printf("The comparator function is missing\n");
		return NULL;
	}

	if (df == NULL)
	{
		printf("The destructor function is missing\n");
		return NULL;
	}

	return NULL;
}

void SLDestroy(SortedListPtr list)
{
}

int SLInsert(SortedListPtr list, void *newObj)
{
	return 0;
}

int SLRemove(SortedListPtr list, void *newObj)
{
	return 0;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
	return NULL;
}

void SLDestroyIterator(SortedListIteratorPtr iter)
{
}

void *SLGetItem(SortedListIteratorPtr iter)
{
	return NULL;
}

void *SLNextItem(SortedListIteratorPtr iter)
{
	return NULL;
}