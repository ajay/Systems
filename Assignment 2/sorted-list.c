/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * sorted-list.c
 */

#include <stdio.h>
#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
	if (cf == NULL)
	{
		if (df == NULL)
		{
			printf("The comparator and destructor functions are missing\n");
		}
		else
		{
			printf("The comparator function is missing\n");
		}
		return NULL;
	}

	if (df == NULL)
	{
		printf("The destructor function is missing\n");
		return NULL;
	}

	SortedListPtr list = (SortedListPtr) malloc(sizeof(struct SortedList));
	list->head = NULL;
	list->compare = cf;
	list->destroy = df;
	return list;
}

void SLDestroy(SortedListPtr list)
{
	if (list == NULL)
		return;

	NodePointer nodeToDelete;
	while (list->head != NULL)
	{
		nodeToDelete = list->head;
		list->head = list->head->next;
		list->destroy(nodeToDelete->data);
		free(nodeToDelete);
	}
	free(list);
}

// Return 1 if Succsessful, 0 if insert failed
int SLInsert(SortedListPtr list, void *newObj)
{
	if (list == NULL)
	{
		printf("The list given to SLInsert was NULL\n");
		return 0;
	}

	NodePointer nodeToInsert = (NodePointer) malloc(sizeof(struct Node));
	nodeToInsert->next = NULL;
	nodeToInsert->data = newObj;

	if (list->head == NULL)
	{
		list->head = nodeToInsert;
		return 1;
	}

	NodePointer tempNode;

	while (list->head != NULL)
	{
		tempNode = list->head;
		list->head = list->head->next;
	}

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