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
	int one = *(int*)pOne;
	int two = *(int*)pTwo;
	return (one - two);
}

void destroy(void *data)
{
	printf("I DESTROYED THE DATA\n");
	return;
}

int main(int argc, char **argv)
{
    printf("This is the main file\n");

    // Test Case 1 (Integers)
	printf("\e[1;32mTest Case 1: \n\e[0m");
    SortedListPtr test1 = SLCreate(compareInts, destroy);
	int intArray[10] = {9, 32, 48, 61, 1, 31, 4, 11, 12};

	int i;

	for(i=0; i<(sizeof(intArray) / sizeof(intArray[0])); i++)
	{
		if(SLInsert(test1, (void *)intArray[i]) == 0)
			printf("\e[1;31mThere was an error\n\e[0m");
	}
	SLDestroy(test1);
	return 0;
}