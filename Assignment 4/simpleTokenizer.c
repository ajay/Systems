/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * simpleTokenizer.c for pa4:Indexer
 */

#include "simpleTokenizer.h"

#define reset   "\x1b[0m"
#define red     "\x1b[31m"

struct TokenizerT
{
	char *inputString;
	char *oldToken;
	char *token;
	char *start;
	char *current;
};

typedef struct TokenizerT Tokenizer;

Tokenizer *TKCreate(char *originalString)
{
	if ((sizeof originalString == 0) || (originalString == NULL))
	{
		printf(red "ERROR: You tried to create a token from a NULL input string\n" reset);
		return NULL;
	}

	Tokenizer *tokenizer;
	tokenizer = malloc(sizeof(Tokenizer));
	tokenizer->inputString = malloc(sizeof(char)*strlen(originalString)+1);
	strcpy(tokenizer->inputString, originalString);
	tokenizer->start = tokenizer->inputString;
	tokenizer->current = tokenizer->inputString;
	tokenizer->oldToken = NULL;
	return tokenizer;
}

void TKDestroy(Tokenizer *tokenizer)
{
	if (tokenizer == NULL)
		printf(red "ERROR: You tried to destroy a NULL Tokenizer\n" reset);

	if (tokenizer->inputString != NULL)
		free(tokenizer->inputString);
	if (tokenizer != NULL)
		free(tokenizer);
}

char *TKGetNextToken(Tokenizer *tokenizer)
{
	if (tokenizer->oldToken != NULL)
		free(tokenizer->oldToken);

	if (tokenizer == NULL)
	{
		printf(red "ERROR: You tried to get the next token of NULL\n" reset);
		return NULL;
	}

	while ((tokenizer != NULL) && (tokenizer->start[0] != '\0'))
	{
		if (isalpha(tokenizer->current[0]) != 0)
		{
			while (isalnum(tokenizer->current[0]) != 0)
			{
				tokenizer->current++;
			}

			int length = strlen(tokenizer->start) - strlen(tokenizer->current);
			tokenizer->token = (char*)malloc(sizeof(char)*length+1);

			strncpy(tokenizer->token, tokenizer->start, length);
			tokenizer->token[length] = '\0';

			tokenizer->start = tokenizer->current;
			tokenizer->oldToken = tokenizer->token;

			return tokenizer->token;
		}
		else
		{
			tokenizer->start++;
			tokenizer->current = tokenizer->start;
		}
	}
	return NULL;
}