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

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

int main(int argc, char **argv)
{
    printf("This is the main file\n");
    // SortedListPtr test = SLCreate(NULL, NULL);
    



	const char * stringArray[] = {"Tom", "Jerry"};
	void *printer;
	SortedListPtr sl2 = SLCreate(compareStrings, destroyBasicTypeNoAlloc);
	int i;
	
	for(i=0; i<(sizeof(stringArray)/sizeof(stringArray[0])); i++){
		if(SLInsert(sl2, (void *)stringArray[i])==0)
			printf("There was an error\n");
	}


    return 0;
}