/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * main.c for mallocEnh.c
 */
 
#include <stdio.h>
#include <stdlib.h> 
#include "mallocEnh.h"

int main(int argc, char **argv)
{
	// void *p = NULL;
	// p = malloc(1000);
	// p = 10765;
	// printf("This is p: %d\n", p);

	//  char * test = malloc(0);
	//  // void *p = (char *)malloc(200);
	// // void *t = malloc(5);
	// // free(test);
	// // free(p+2);
	// // free(p);
	// // free(NULL);
	// // int x = 10;
	// // free(&x);



	// // void *p;
	// // free(p);
	// char *shit = malloc(20);
	// free(NULL);
	// // free(shit+122);

	// free(shit);
//	shit = "hello";
	// printf("shit: %s\n", shit);
	// free(shit);
	// free(shit);
	// char *shit = malloc(1000);
	// free(shit);
	// free(shit);


	char *p = (char *)malloc( 200 );
	free(p);

	return 0;
}