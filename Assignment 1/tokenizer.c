/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * tokenizer.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
// #include <ctype.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_
{
	char *inputString;
	char *token;
	char *start;
	char *current;
	int type;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *originalString)
{
	if (sizeof originalString == 0)
	{
		return NULL;
	}

	TokenizerT *newToken;
	newToken = malloc(sizeof(struct TokenizerT_));
	newToken->inputString = malloc(sizeof(char)*strlen(originalString)+1);
	strcpy(newToken->inputString, originalString);
	newToken->start = newToken->inputString;
	newToken->current = newToken->inputString;
	return newToken;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT * tk)
{

}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *input) 
{	
	int foundToken = 0;

	while ((input != NULL) && (input->start[0] != '\0'))
	{
		// Skip spaces, etc.
		if (input->start[0] == 0x20)
		{
			input->start++;
			input->current++;
		}

		// Words
		else if (isalpha(input->current[0]) != 0)
		{
			while (isalnum(input->current[0]) != 0)
			{
				input->current++;
			}

			int length = strlen(input->start) - strlen(input->current);
			input->token = (char*)malloc(sizeof(char)*length+1);

			strncpy(input->token, input->start, length);
			input->token[length] = '\0';

			input->start = input->current;
			
			return input->token;
		}

		// Numbers
		else if(isdigit(input->current[0]) !=0)
		{
			while(isdigit(input->current[0]) != 0)
			{
				input->current++;
			}

			int length = strlen(input->start) - strlen(input->current);
			input->token = (char*)malloc(sizeof(char)*length+1);

			strncpy(input->token, input->start, length);
			input->token[length] = '\0';

			input->start = input->current;
			
			return input->token;

		}

		else
		{
			printf("Exit because error\n");
			return NULL;
		}
	}
	printf("Exit because end of input reached\n");
	return NULL;
} 

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("INVALID NUMBER OF ARGUMENTS\n");
		return 0;
	}

	TokenizerT *input = TKCreate(argv[1]);
	char *tokens = " ";

	while (tokens != NULL)
	{
		tokens = TKGetNextToken(input);
		if (tokens != NULL)
			printf("Token is: %s\n", tokens);
	} 

	return 0;
}