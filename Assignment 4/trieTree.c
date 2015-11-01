/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * trieTree.c for pa4:Indexer
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trieTree.h"

#define reset	"\x1b[0m"
#define	red		"\x1b[31m"
#define green	"\x1b[32m"

trieNodePointer ROOT = NULL;
int totalNodes;
int nodeCount;
char *output;

void assignRoot(trieNodePointer root)
{
	ROOT = root;
}

int parseChar(char c)
{
	if (isalpha(c))
		return (int)(c - 97);
	else if (((int)c >= 48) && ((int)c <= 57))
		return (int)(c - 22);
	printf(red "ERROR: Can not parse character: " green "%c\n" reset, (char)c);
	return -1;
}

char reverseParse(int c)
{
	if ((c >= 0) && (c <= 25))
		return (char)(c + 97);
	else if ((c >= 26) && (c <= 35))
		return (int)(c + 22);
	printf(red "ERROR: Can not reverse parse integer: " green "%c\n" reset, (int)c);
	return -1;
}

void resetVisited(trieNodePointer root)
{
	for (int i=0; i < 36; i++)
	{
		if (root->children[i] != NULL)
		{
			resetVisited(root->children[i]);
			root->children[i]->visited = false;
		}
	}
}

void total(trieNodePointer root)
{
	for (int i=0; i < 36; i++)
	{
		if (root->children[i] != NULL)
		{
			total(root->children[i]);
			if (root->children[i]->files != NULL)
				totalNodes++;
		}
	}
}

void sortFiles(fileNodePointer rootFile)
{
	if (rootFile->next == NULL)
		return;

	// rootFile->count = 10;
}

fileNodePointer createNewFileNode(char *fileName)
{
	fileNodePointer f = (fileNodePointer) malloc(sizeof(struct fileList));
	f->next = NULL;
	f->fileName = (char *)malloc(strlen(fileName)+1);
	strcpy(f->fileName, fileName);
	f->count = 1;
	return f;
}

trieNodePointer createNewTrieNode()
{
	trieNodePointer t = (trieNodePointer) malloc(sizeof(struct trieNode));

	for (int i = 0; i < ALPHABET_SIZE; i++)
		t->children[i] = NULL;
	t->files = NULL;
	t->visited = false;
	t->token = NULL;
	return t;
}

void trieInsert(trieNodePointer root, char *token, char *inputFilePath)
{
	trieNodePointer currentNode = root;

	for (int i = 0; i < strlen(token); i++)
	{
		if (currentNode->children[parseChar(token[i])] == NULL)
		{
			currentNode->children[parseChar(token[i])] = createNewTrieNode();
			currentNode = currentNode->children[parseChar(token[i])];
		}
		else
		{
			currentNode = currentNode->children[parseChar(token[i])];
		}
		if (i == (strlen(token) - 1))
		{
			if (currentNode->token == NULL)
			{
				currentNode->token = (char *)malloc(sizeof(strlen(token)+1));
				strcpy(currentNode->token, token);
			}
			if (currentNode->files == NULL)
			{
				currentNode->files = createNewFileNode(inputFilePath);
			}
			else
			{
				bool newNode = true;
				fileNodePointer tempFiles = currentNode->files;
				while (tempFiles->next != NULL)
				{
					if (strcmp(tempFiles->fileName, inputFilePath) == 0)
					{
						tempFiles->count++;
						newNode = false;
						break;
					}
					tempFiles = tempFiles->next;
				}
				if (strcmp(tempFiles->fileName, inputFilePath) == 0)
				{
					tempFiles->count++;
				}
				else if (newNode == true)
				{
					tempFiles->next = createNewFileNode(inputFilePath);
				}
			}
			sortFiles(currentNode->files);
		}
	}
}

void printTreeRecursive(trieNodePointer root, FILE *outputFile)
{
	int keepGoing = false;
	for (int i=0; i < 36; i++)
	{
		if (root->children[i] != NULL)
		{
			trieNodePointer currentNode = root->children[i];

			printTreeRecursive(currentNode, outputFile);

			if ((currentNode->files != NULL) && (currentNode->visited == false))
			{
				currentNode->visited = true;
				fileNodePointer tempFiles = currentNode->files;
				fprintf(outputFile, "\t{\"%s\" : [\n", currentNode->token);
				nodeCount++;
				while (tempFiles != NULL)
				{
					fprintf(outputFile, "\t\t{\"%s\" : %d}", tempFiles->fileName, tempFiles->count);
					if (tempFiles->next != NULL)
					{
						fprintf(outputFile, ",");
					}
					fprintf(outputFile, "\n");
					tempFiles = tempFiles->next;
				}
				fprintf(outputFile, "\t]}");
				if (nodeCount < totalNodes)
					fprintf(outputFile, ",");
				fprintf(outputFile, "\n");
				keepGoing = true;
				break;
			}
		}
	}

	if (keepGoing == true)
		printTreeRecursive(ROOT, outputFile);
}

void printTree(trieNodePointer root, char *output)
{
	FILE *outputFile = fopen(output, "w");
	totalNodes = 0;
	nodeCount = 0;
	total(ROOT);
	fprintf(outputFile, "{\"list\" : [\n");
	resetVisited(root);
	printTreeRecursive(root, outputFile);
	fprintf(outputFile, "]}\n");
	fclose(outputFile);
}

void destroyNodes(trieNodePointer root)
{
	int childrenCount = 0;
	for (int i=0; i<36; i++)
	{
		if (root->children[i] != NULL)
			childrenCount++;
	}

	if (childrenCount > 0)
	{
		for (int i=0; i<36; i++)
		{
			if (root->children[i] != NULL)
			{
				destroyNodes(root->children[i]);
			}
		}
	}

	free(root);
	root = NULL;
}

void destroyFiles(trieNodePointer root)
{
	for (int i=0; i<36; i++)
	{
		if (root->children[i] != NULL)
		{
			destroyFiles(root->children[i]);
		}
		if (root->files != NULL)
		{
			fileNodePointer temp = root->files;
			fileNodePointer oldtemp = NULL;
			while (temp != NULL)
			{
				oldtemp = temp;
				temp = temp->next;
				free(oldtemp->fileName);
				free(oldtemp);
			}
			free(temp);
			root->files = NULL;
		}
		if (root->token != NULL)
		{
			free(root->token);
			root->token = NULL;
		}
	}
}

void destroy()
{
	destroyFiles(ROOT);
	destroyNodes(ROOT);
}