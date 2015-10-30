/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * trieTree.h for pa4:Indexer
 */

#ifndef TRIETREE_H
#define TRIETREE_H

struct fileList;

typedef struct fileList *fileListNode;

struct trieNode;

typedef struct trieNode *trieNodePointer;

int parseChar(int c);

fileListNode createNextFileNode(char *fileName);

trieNodePointer createNewTrieNode();

#endif