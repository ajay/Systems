/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * trieTree.c for pa4:Indexer
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trieTree.h"

#define ALPHABET_SIZE 36

struct fileList
{
	struct fileList *next;
	char *fileName;
	int count;
};
typedef struct fileList *fileListNode;

struct trieNode
{
	struct trieNode *children[ALPHABET_SIZE];
	fileListNode files;
};
typedef struct trieNode *trieNodePointer;

int parseChar(int c)
{
	if (isalpha(c))
		return (int)(c - 97);
	else if ((c >= 0) && (c <= 9))
		return (int)(c + 26);
	return -1;
}

fileListNode createNextFileNode(char *fileName)
{
    fileListNode f = (fileListNode) malloc(sizeof(struct fileList));
    f->next = NULL;
    f->fileName = fileName;
    f->count = 1;
	return f;
}

trieNodePointer createNewTrieNode()
{
    trieNodePointer t = (trieNodePointer) malloc(sizeof(struct trieNode));

	for (int i = 0; i < ALPHABET_SIZE; i++)
		t->children[i] = NULL;
	t->files = NULL;

	return t;
}