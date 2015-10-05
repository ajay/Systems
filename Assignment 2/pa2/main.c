/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * main.c for sorted-list.c
 */

#include <stdio.h>
#include <string.h>
#include "sorted-list.h"

/* 
 * Test Comparator Functions
 * <0 if the First Object is Smaller 	(if Obj 1 < Obj 2)
 * =0 if the Two Objects are equal		(if Obj 1 == Obj 2)
 * >0 if the Second Object is Smaller 	(if Obj 1 > Obj 2)
 */
int compareInts(void *pOne, void *pTwo)
{
    int one = *(int*) pOne;
    int two = *(int*) pTwo;
    return (one - two);
}

int compareDoubles(void *pOne, void *pTwo)
{
    double one = *(double*) pOne;
    double two = *(double*) pTwo;
	if (one == two)
		return 0;
	if (one < two)
        return -1;
    return 1;
}

int compareStrings(void *pOne, void *pTwo)
{
	char *one = pOne;
	char *two = pTwo;
    return strcmp(one, two);
}

/*
 * Test Destructor Functions
 */
void destroy(void *data)
{
	return;
}

void destroyAllocated(void *data)
{
	free(data);
	return;
}

int main(int argc, char **argv)
{
	// Test Case 0 (NULL Input()
	printf("\n\e[1;32mTest Case 0: \n\e[0m");
	SLCreate(NULL, NULL);

    // Test Case 1 (Integers)
	printf("\n\e[1;32mTest Case 1: \n\e[0m");
    SortedListPtr test1 = SLCreate(compareInts, destroy);
	int intArray[10] = {9, 32, 48, 61, 1, 31, 4, 11, 12, -4314};

	int i;
	for(i=0; i<10; i++)
	{
		if(SLInsert(test1, &intArray[i]) == 0)
		{
			printf("\e[1;34mThere was an error received from SLInsert\n\e[0m");
		}
	}
	printSortedList(test1, "int");
	
	// Test Case 2 (Adding duplicate into list)
	printf("\n\e[1;32mTest Case 2: \n\e[0m");
	int a = 4;
	SLInsert(test1, &a); 

	// Test Case 3 (Destroy List)
	printf("\n\e[1;32mTest Case 3: \n\e[0m");
	SLDestroy(test1);

	// Test Case 4 (Compare Doubles)
	printf("\n\e[1;32mTest Case 4: \n\e[0m");

    SortedListPtr test2 = SLCreate(compareDoubles, destroy);
	double doubleArray[10] = {9.2, 32.41, 48.2, 6.1, 1, 1.5, .4, 1.1, 1.2, -43.14};

	for(i=0; i<10; i++)
	{
		if(SLInsert(test2, &doubleArray[i]) == 0)
		{
			printf("\e[1;34mThere was an error received from SLInsert\n\e[0m");
		}
	}
	printSortedList(test2, "double");

	// Test Case 5 (Remove object not in list)
	printf("\n\e[1;32mTest Case 5: \n\e[0m");
	printf("Original List: ");
	printSortedList(test2, "double");
	double b = 1.0;
	SLRemove(test2, &b);
	printf("Removed  List:  ");
	printSortedList(test2, "double");
	SLRemove(test2, &b);
	SLDestroy(test2);
	return 0;
}