/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * trieTree.h for pa4:Indexer
 */

#ifndef TRIETREE_H
#define TRIETREE_H

#include <stdbool.h>
#define ALPHABET_SIZE 36

struct fileList
{
	struct fileList *next;
	char *fileName;
	int count;
};
typedef struct fileList *fileNodePointer;

struct trieNode
{
	struct trieNode *children[ALPHABET_SIZE];
	fileNodePointer files;
	bool visited;
	char *token;
};
typedef struct trieNode *trieNodePointer;

void assignRoot(trieNodePointer root);

trieNodePointer createNewTrieNode();

void trieInsert(trieNodePointer root, char *token, char *inputFilePath);

void printTree(trieNodePointer root, char *output);

void destroy();

#endif