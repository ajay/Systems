/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * tokenizer.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ 
{
	char *inputString;
	char *token;
	char *start;
	char *end;
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

TokenizerT *TKCreate(char * ts)
{
	struct TokenizerT_ *newToken;
	newToken = malloc(sizeof(struct TokenizerT_));
	newToken->inputString = malloc(sizeof(char)*strlen(ts)+1);

	newToken->inputString = ts;




	// memset(newToken->tokenNumber, 0, sizeof(int) * strlen(ts));
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

char *TKGetNextToken(TokenizerT * tk) 
{
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

	if(argc != 2){
		printf("INVALID NUMBER OF ARGUMENTS\n");
		return 0;
	}

	struct TokenizerT_ *token = TKCreate(argv[1]);
	printf("%s !!!!\n", token->inputString);

	// int i;
// 	for(i=0; i<k; i++){
// 	printf("%d \n",token->tokenNumber[i]);
// }

	return 0;
}