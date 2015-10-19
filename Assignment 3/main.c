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

	char * dsfsd = malloc(95);
    char * jim = malloc(162);
    
    char * json = malloc(30);
    char * mal = malloc(30);
    char * roy = malloc(15);
    
    free(roy);
    roy = malloc(15);
    free(roy);
	return 0;
}