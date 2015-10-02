#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"

/*By Vincent Khong and Andrew Yoon*/

int compareInts (void * p1, void * p2) {
    int first = *(int *) p1;
    int second = *(int *) p2;
    if (first == second) {
        return 0;
    } else if (first < second) {
        return -1;
    }
    return 1;
}

int compareDoubles (void * p1, void * p2) {
    double first = *(double *) p1;
    double second = *(double *) p2;
    if (first == second) {
        return 0;
    } else if (first < second) {
        return -1;
    }
    return 1;
}

int compareStrings (void * p1, void * p2) {
    char * first = p1;
    char * second = p2;
    return strcmp(first, second);
}

void destroyInts (void * p1) {
    return;
}

int main()
{
    SortedListPtr sl = SLCreate(compareInts, destroyInts);

    int a, b, c, d, e, f, *p1;
    a = 20;
    b = 15;
    c = 10;
    d = 3;
    e = 2;
    f = 1;
    p1 = malloc(sizeof(int));
    p1 = &a;
    SLInsert(sl, p1);
    p1 = &b;
    SLInsert(sl, p1);
    p1 = &c;
    SLInsert(sl, p1);
    p1 = &d;
    SLInsert(sl, p1);
    p1 = &e;
    SLInsert(sl, p1);
    p1 = &f;
    SLInsert(sl, p1);
    printf("LL expected output: 20, 15, 10, 3, 2, 1\n");
    printf("Actual output: \n");
    node * ptr;
    ptr = sl -> head;
    while (ptr != NULL) {
        printf("%d\t", *(int *)(ptr -> pData));
        ptr = ptr -> next;
    }
    printf("\n");
    printf("\n");

    p1 = &f;
    SLRemove(sl, p1);
    p1 = &a;
    SLRemove(sl, p1);
    ptr = sl -> head;
    printf("LL expected output: 15, 10, 3, 2\n");
    printf("Actual output: \n");
    while (ptr != NULL) {
        printf("%d\t", *(int *)(ptr -> pData));
        ptr = ptr -> next;
    }
    printf("\n");
    printf("\n");
    printf("Iterator pointer begins here: \n");
    printf("LL expected output: 15, 10, 3, 2\n");
    printf("Actual output; \n");
    SortedListIteratorPtr si;
    si = SLCreateIterator(sl);
    printf("%d\t", *(int*)SLGetItem(si));
    while (1) {
        p1 = SLNextItem(si);
        if (p1 == NULL)
            break;
        printf("%d\t", *p1);
    }
    printf("\n");
    printf("\n");


    p1 = &d;
    SLRemove(sl, p1);
    p1 = &c;
    SLRemove(sl, p1);
    si -> currNode = sl -> head;
    printf("Expected output: 10, 3\n");
    printf("%d\t", *(int*)SLGetItem(si));
    while (1) {
        p1 = SLNextItem(si);
        if (p1 == NULL)
            break;
        printf("%d\t", *p1);
    }
    printf("\n");
    printf("\n");


    free(p1);
    SLDestroyIterator(si);
    SLDestroy(sl);
    return 0;
}

