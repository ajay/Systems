/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * main.c for sorted-list.c
 */

#include <stdio.h>
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

int main(int argc, char **argv)
{
    printf("This is the main file\n");
    // SortedListPtr test = SLCreate(NULL, NULL);
    return 0;
}