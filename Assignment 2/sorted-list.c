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
            printf("ERROR: The comparator and destructor functions are missing\n");
        }
        else
        {
            printf("ERROR: The comparator function is missing\n");
        }
        return NULL;
    }
    
    if (df == NULL)
    {
        printf("ERROR: The destructor function is missing\n");
        return NULL;
    }
    
    SortedListPtr list = (SortedListPtr) malloc(sizeof(struct SortedList));
    
    if(list == NULL)
    {
        printf("ERROR: There was no memory to be allocated for the new sorted list\n");
        return NULL;
    }
    
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
        printf("ERROR: The list given to SLInsert was \'NULL\'\n");
        return 0;
    }
    
    NodePointer nodeToInsert = (NodePointer) malloc(sizeof(struct Node));
    nodeToInsert->next = NULL;
    nodeToInsert->data = newObj;
    nodeToInsert->numberOfPointers = 0;
    nodeToInsert->isHead = 0;
    
    if (list->head == NULL)
    {
        list->head = nodeToInsert;
        list->head->isHead = 1;
        list->head->numberOfPointers = 1;
        return 1;
    }
    
    NodePointer prevNode = NULL;
    NodePointer nodeToRemove = list->head;
    
    while (nodeToRemove != NULL)
    {

        if(list->compare(nodeToRemove->data, nodeToInsert->data) == 0)
        {
            list->destroy(nodeToInsert->data);
            free(nodeToInsert);
            printf("ERROR: The data to insert was already present in the list\n");
            return 0;
        }
        else if(list->compare(nodeToRemove->data, nodeToInsert->data) == -1)
        {
            break;
        }
        prevNode = nodeToRemove;
        nodeToRemove = nodeToRemove->next;
    }
    
    // New node will become new head
    if(nodeToRemove == list->head)
    {
        list->head = nodeToInsert;
        list->head->next= nodeToRemove;
        list->head->numberOfPointers++;
        list->head->isHead = 1;
        nodeToRemove->isHead = 0;
        return 1;
    }

    // Node to insert is the new last node
    else if(nodeToRemove == NULL) 
    {
        prevNode->next = nodeToInsert;
        nodeToInsert->numberOfPointers++;
        return 1;
    }

    // General case, node to insert is in the middle
    else
    {
        nodeToInsert->next = nodeToRemove;
        nodeToInsert->numberOfPointers++;
        prevNode->next = nodeToInsert;
        return 1;
    }

    printf("ERROR: There was an unknown error in SLInsert\n");
    return 0;
}

// Remove object which contains the given data
int SLRemove(SortedListPtr list, void *newObj)
{
    if (list == NULL)
    {
        printf("ERROR: There was no list given\n");
        return 0;
    }

    if (newObj == NULL)
    {
        printf("ERROR: There was no data given\n");
        return 0;
    }
    
    NodePointer prevNode = NULL;
    NodePointer nodeToRemove = list->head;
    
    // Case where head needs to be removed
    if(nodeToRemove->data == newObj)
    {
        list->head = list->head->next;
        list->head->isHead = 1;

        nodeToRemove->numberOfPointers--;

        if (nodeToRemove->numberOfPointers == 0)
        {
            list->destroy(nodeToRemove->data);
            free(nodeToRemove);
        }

        return 1;
    }

    // Case where object to remove is in the middle or end
    while (nodeToRemove != NULL)
    {
        if(nodeToRemove->data == newObj)
        {
            prevNode->next = nodeToRemove->next;
            nodeToRemove->numberOfPointers--;
            if (nodeToRemove->numberOfPointers == 0)
            {
                list->destroy(nodeToRemove->data);
                free(nodeToRemove);
            }
            return 1;
        }
        prevNode = nodeToRemove;
        nodeToRemove = nodeToRemove->next;
    }

    printf("ERROR: Object to remove not found in list\n");
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