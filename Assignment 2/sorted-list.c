/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * sorted-list.c
 */

#include <stdio.h>
#include <string.h>
#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
    if (cf == NULL)
    {
        if (df == NULL)
        {
            printf("\e[1;31mERROR: The comparator and destructor functions are missing (what you doin?)\n\e[0m");
        }
        else
        {
            printf("\e[1;31mERROR: The comparator function is missing (lol srsly?)\n\e[0m");
        }
        return NULL;
    }
    
    if (df == NULL)
    {
        printf("\e[1;31mERROR: The destructor function is missing (really? u srs?)\n\e[0m");
        return NULL;
    }
    
    SortedListPtr list = (SortedListPtr) malloc(sizeof(struct SortedList));
    
    if (list == NULL)
    {
        printf("\e[1;31mERROR: There was no memory to be allocated for the new sorted list (sum real shit went wrong)\n\e[0m");
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
        printf("\e[1;31mERROR: The list given to SLInsert was \'NULL\' (where my list at)\n\e[0m");
        return 0;
    }

    if (newObj == NULL)
    {
        printf("\e[1;31mERROR: The object given to SLInsert was \'NULL\' (U GAaY whatchu doin)\e[0m");
        return 0;
    }
    
    NodePointer nodeToInsert = (NodePointer) malloc(sizeof(struct Node));
    nodeToInsert->next = NULL;
    nodeToInsert->data = newObj;
    nodeToInsert->numberOfPointers = 0;

    if (list->head == NULL)
    {
        list->head = nodeToInsert;
        list->head->numberOfPointers = 1;
        return 1;
    }
    
    NodePointer prevNode = NULL;
    NodePointer currentNode = list->head;

    while (currentNode != NULL)
    {
        if (list->compare(currentNode->data, newObj) == 0)
        {
            list->destroy(nodeToInsert->data);
            free(nodeToInsert);
            printf("\e[1;31mERROR: The data to insert was already present in the list (gg no re)\n\e[0m");
            return 0;
        }

        if (list->compare(currentNode->data, newObj) <= -1)
        {
            break;
        }
        
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    
    // New node will become new head
    if (currentNode == list->head)
    {
        list->head = nodeToInsert;
        list->head->next= currentNode;
        list->head->numberOfPointers++;
        return 1;
    }

    // Node to insert is the new last node
    else if (currentNode == NULL) 
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

    printf("\e[1;31mERROR: There was an unknown error in SLInsert (SHIIIEEEETTT U rlly fucked up lel)\n\e[0m");
    return 0;
}

// Remove object which contains the given data
int SLRemove(SortedListPtr list, void *newObj)
{
    if (list == NULL)
    {
        printf("\e[1;31mERROR: There was no list given (why u playin doe)\n\e[0m");
        return 0;
    }

    if (newObj == NULL)
    {
        printf("\e[1;31mERROR: There was no data given (why u tease me?)\n\e[0m");
        return 0;
    }
    
    NodePointer prevNode = NULL;
    NodePointer nodeToRemove = list->head;
    
    // Case where head needs to be removed
    if (nodeToRemove->data == newObj)
    {
        list->head = list->head->next;
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
        if (nodeToRemove->data == newObj)
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

    printf("\e[1;31mERROR: Object to remove not found in list (lol u tryna trick me)\n\e[0m");
    return 0;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
    if (list == NULL)
    {
        printf("ERROR: The list given to SLCreateIterator was \'NULL\' (not allocated)\n");
        return NULL;
    }

    if (list->head == NULL)
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
    if (iterator == NULL)
    {
        printf("ERROR: The iterator given to SLDestroyIterator was \'NULL\'\n");
        return;
    }

    iterator->currentNode->numberOfPointers--;

    if (iterator->currentNode->numberOfPointers <= 0)
    {
        iterator->destroy(iterator->currentNode->data);
        free(iterator->currentNode);
    }

    free(iterator);
}

void *SLGetItem(SortedListIteratorPtr iterator)
{
    if (iterator == NULL)
    {
        printf("Iterator = Null \n");
        return NULL;
    }
    else if (iterator->currentNode == NULL)
    {
        printf("Iterator.currentNode = Null \n");
        return NULL;
    }
    return iterator->currentNode->data;
}

void *SLNextItem(SortedListIteratorPtr iterator)
{
    if (iterator == NULL)
    {
        printf("Iterator = Null \n");
        return NULL;
    }
    else if(iterator->currentNode == NULL)
    {
        printf("Iterator.currentNode = Null \n");
        return NULL;
    }

    iterator->currentNode->numberOfPointers--;
    NodePointer prevNode = iterator->currentNode;
    iterator->currentNode = iterator->currentNode->next;
    iterator->currentNode->numberOfPointers++;

    //If it was previously removed from the list
    if (prevNode->numberOfPointers == 0 ) 
    {
        iterator->destroy(prevNode->data);
        free(prevNode);
    }

    //If it is the last item
    if (iterator->currentNode == NULL) 
    { 
        return NULL;
    }

    return iterator;
}

void printSortedList(SortedListPtr list, char *type)
{
	if (list == NULL)
	{
		printf("Dumbass you didn't even gimme a list\n");
		return;
	}
	
	if (list->head == NULL)
	{
		printf("Dumbass the list is empty");
		return;
	}

	printf("Sorted List: {");
	NodePointer nodeToPrint = list->head;
    while (nodeToPrint != NULL)
    {
    	if (strcmp(type, "int") == 0)
    		printf("%d", *(int*)nodeToPrint->data);
    	if (strcmp(type, "double") == 0)
    		;
//    		printf("%lf", *(double*)nodeToPrint->data);
    	if (nodeToPrint->next != NULL)
    		printf(", ");
        nodeToPrint = nodeToPrint->next;
    }
    printf("}\n");
}