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
    
    if(list == NULL)
    {
        return NULL;  /*Returns null if there is no memory left to be allocated*/
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
        printf("The list given to SLInsert was NULL\n");
        return 0;
    }
    
    NodePointer nodeToInsert = (NodePointer) malloc(sizeof(struct Node));
    nodeToInsert->next = NULL;
    nodeToInsert->data = newObj;
    nodeToInsert->count = 0;
    nodeToInsert->front = 0;
    
    if (list->head == NULL)
    {
        list->head = nodeToInsert;
        list->head->front = 1;
        return 1;
    }
    
    NodePointer prevNode = NULL;
    NodePointer currNode = list->head;
    
    while (currNode != NULL)
    {
        if(list->compare(currNode->data, nodeToInsert->data) == 0) // Don't need to insert the same data again
        {
            list->destroy(nodeToInsert->data); //to hide the data
            free(nodeToInsert);
            return 0;
        }
        else if(list->compare(currNode->data, nodeToInsert->data) == -1)
        {
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    
    if(currNode == list->head) /*node to insert is at the start*/
    {
        list->head = nodeToInsert;
        list->head->front = 1;
        currNode->front = 0;
        currNode->count++;
        list->head->next= currNode;
        return 1;
    }
    else if(currNode == NULL) /* node to insert is at the end*/
    {
        prevNode->next = nodeToInsert;
        nodeToInsert->count++;
        return 1;
    }
    else /*node to insert is in the middle*/
    {
        nodeToInsert->next = currNode;
        nodeToInsert->count++;
        prevNode->next = nodeToInsert;
        return 1;
    }
    
    return 0;
    
    
}
/*Remove object which contains the given data*/
int SLRemove(SortedListPtr list, void *newObj)
{
    // if(list == NULL || newObj == NULL)/*If there is nothing to delete return 0*/
    // {
    //     return 0;
    // }
    
    // NodePointer prevNode = NULL;
    // NodePointer currNode = list->head;
    
    // if(list->head->data == newObj)
    // {
    //     list->head = list->head->next;
    //     list->head->count--;
    //     list->destroy(currNode->data);
    //     free(currNode);
    //     return 1;
    // }
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