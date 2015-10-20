/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * main.c for mallocEnh.c
 */
 
#include <stdio.h>
#include <stdlib.h> 
#include "mallocEnh.h"

#define reset   "\x1b[0m"
#define green   "\x1b[32m"

int main(int argc, char **argv)
{
	printf(green "Test Case 1: " reset);
	// 1. // Trying to free unallocated block
	// Input:
		int puff;
		free(&puff);
	// Expected Output: ERROR: free() cannot free a pointer that was not dynamically allocated. An item on line 19 of main.c may have caused this.
	printf("\n");

	printf(green "Test Case 2: " reset);
	// 2. // Trying to free dynamic memory not returned from malloc()
	// Input:
		char *lol = (char*) malloc(200);
		free(lol + 10); 
	// Expected Output:  ERROR: free() cannot free a pointer that was not returned from malloc. An item on line 27 of main.c may have caused this.
	printf("\n");

	printf(green "Test Case 3: " reset);
	// 3. // Redundant freeing of the same pointer
	// Input
		char *buns = (char*) malloc(100);
		free(buns); // haha get it?
		free(buns);
	// Expected Output: ERROR: free() cannot free a pointer that is unallocated. An item on line 36 of main.c may have caused this.
	printf("\n");

	printf(green "Test Case 4: " reset);
	// 4. //Trying to allocate a block of size 0
	// Input:
		buns = (char*) malloc(0);
	// Expected Output: ERROR: free() cannot free a pointer that is unallocated. An item on line 36 of main.c may have caused this.
	printf("\n");

	printf(green "Test Case 5: " reset);
	// 5. // Test saturation
	// Input: 
		char *pebble = (char*)malloc(100000000);
		free(pebble);
	// Expected Output: Nothing (Memory allocated and freed)
	printf("\n\n");

	printf(green "Test Case 6: " reset);
	// 6.// Regular case
	// Input:	
		void* test = malloc(1);
		test = (char*)malloc(100);
		free(test);
		test = (char*)malloc(100);
		free(test);
	// Expected Output: Nothing (Memory allocated and freed)
	printf("\n\n");

	return 0;
}