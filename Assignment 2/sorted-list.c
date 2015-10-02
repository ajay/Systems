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
    
    // NodePointer prevNode = (NodePointer) malloc(sizeof(struct Node));
    NodePointer prevNode = NULL;
    // NodePointer currentNode = (NodePointer) malloc(sizeof(struct Node));
    NodePointer currentNode = list->head;

    while (currentNode != NULL)
    {
        if(list->compare(currentNode->data, newObj) == 0)
        {
            list->destroy(nodeToInsert->data);
            free(nodeToInsert);
            printf("ERROR: The data to insert was already present in the list\n");
            return 0;
        }

        if(list->compare(currentNode->data, newObj) == -1)
        {
            printf("I reached here\n");
            break;
        }
        
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    
    // New node will become new head
    if(currentNode == list->head)
    {
        list->head = nodeToInsert;
        list->head->next= currentNode;
        list->head->numberOfPointers++;
        list->head->isHead = 1;
        currentNode->isHead = 0;
        return 1;
    }

    // Node to insert is the new last node
    else if(currentNode == NULL) 
    {
        prevNode->next = nodeToInsert;
        nodeToInsert->numberOfPointers++;
        return 1;
    }

    // General case, node to insert is in the middle
    else
    {
        nodeToInsert->next = currentNode;
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
        
        if (list->head != NULL)
        {
            list->head->isHead = 1;
        }

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
    if(list == NULL)
    {
        printf("ERROR: The list given to SLCreateIterator was \'NULL\' (not allocated)\n");
        return NULL;
    }

    if(list->head == NULL)
    {
        printf("ERROR: The list given to SLCreateIterator was empty'\n");
        return NULL;
    }

    SortedListIteratorPtr iterator = (SortedListIteratorPtr) malloc(sizeof(struct SortedListIterator));
    iterator->currentNode = list->head;
    list->head->numberOfPointers++;

    return iterator;
}

void SLDestroyIterator(SortedListIteratorPtr iterator)
{
    //get rid of data in itertaor, then get rid of iterator, then decrease number of pointers,
    if(iterator == NULL)
    {
        printf("ERROR: The iterator given to SLDestroyIterator was \'NULL\'\n");
        return;
    }

    iterator->currentNode->numberOfPointers--;

    if(iterator->currentNode->numberOfPointers == 0)
    {
        // list->destroy(iterator->currentNode->data);
        free(iterator->currentNode);
    }

    free(iterator);
}

void *SLGetItem(SortedListIteratorPtr iter)
{
    return NULL;
}

void *SLNextItem(SortedListIteratorPtr iter)
{
    return NULL;
}