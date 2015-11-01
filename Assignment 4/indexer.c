/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * indexer.c for pa4:Indexer
 */

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "simpleTokenizer.h"
#include "trieTree.h"

#define reset	"\x1b[0m"
#define	red		"\x1b[31m"
#define green	"\x1b[32m"

static trieNodePointer root = NULL;

bool isADirectory(char *inputDir)
{
	struct stat buf;
	stat(inputDir, &buf);
	if (S_ISDIR(buf.st_mode) == 1)
		return true;
	return false;
}

int indexTokens(char *inputFilePath)
{
	FILE *inputFile = fopen(inputFilePath, "r");
	if (inputFile == NULL)
	{
		fprintf(stderr, red "ERROR IN INPUT FILE: " green "%s" red " --> ", inputFilePath);
		perror(""); printf(reset);
		return -1;
	}

	fseek(inputFile, 0, SEEK_END);
	long inputFileSize = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);

	char *buffer = NULL;
	buffer = malloc(inputFileSize+1);
	if (buffer == NULL)
	{
		printf(red "ERROR: Cannot malloc size " green "%ld" red " for the input buffer\n", inputFileSize);
		fclose(inputFile);
		return -1;
	}

	if (fread(buffer, inputFileSize, 1, inputFile) != 1)
	{
		fprintf(stderr, red "ERROR READING FROM INPUT FILE: " green "%s" red " --> ", inputFilePath);
		perror(""); printf(reset);
		fclose(inputFile);
		free(buffer);
		return -1;
	}

	fclose(inputFile);
	buffer[inputFileSize] = '\0';

	Tokenizer *tokenizer = TKCreate(buffer);
	if (tokenizer == NULL)
	{
		printf(red "ERROR: There was a problem creating a Tokenizer object in indexTokens()" reset);
		return -1;
	}

	free(buffer);

	char *token = NULL;
	while((token = TKGetNextToken(tokenizer)) != NULL)
	{
		if (token != NULL)
		{
			trieInsert(root, token, inputFilePath);
		}
	}

	TKDestroy(tokenizer);
	return 0;
}

void recurseDir(char *input)
{
	DIR *dirPointer;
	if ((dirPointer = opendir(input)) != NULL)
	{
		struct dirent *dir;
		while ((dir = readdir(dirPointer)) != NULL)
		{
			if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
			{
				continue;
			}

			int dirNameLength = strlen(input);
			int fileNameLength = strlen(dir->d_name);
			char buffer[dirNameLength+fileNameLength+1];
			memcpy(buffer, input, dirNameLength);

			if (input[dirNameLength-1] == '/')
			{
				memcpy(buffer+dirNameLength, dir->d_name, fileNameLength+1);
			}
			else
			{
				buffer[dirNameLength] = '/';
				memcpy(buffer+dirNameLength+1, dir->d_name, fileNameLength+1);
			}

			if (isADirectory(buffer) == 1)
			{
				recurseDir(buffer);
			}
			else
			{
				indexTokens(buffer);
			}
		}
		closedir(dirPointer);
	}
	else
	{
		printf(red "ERROR: There was an error opening this directory: " green "%s\n" reset, input);
		return;
	}
}

int main(int argc, char **argv)
{
	// if (argc != 3)
	// {
	// 	printf(red "ERROR: Invalid number of arguments\nUsage: ./indexer <Output: inverted-index file> <Input: directory or file>\n" reset);
	// 	return 1;
	// }

	// char *output = argv[1];
	// char *input = argv[2];

	char *input = "testDir/example";
	char *output = "output.txt";

	root = createNewTrieNode();

	assignRoot(root);

	recurseDir(input);

	printTree(root, output);

	destroy();

	return 0;
}