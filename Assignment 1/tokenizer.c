/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * tokenizer.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_
{
	char *inputString;
	char *token;
	char *start;
	char *current;
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
	free(tk->inputString);
	free(tk->token);
	free(tk);
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
	while ((input != NULL) && (input->start[0] != '\0'))
	{
		int isASpace = 0;
		int isAWord = 0;

		// Skip spaces, etc.
		if ((input->start[0] == 0x20) || (input->start[0] == 0x09) || (input->start[0] == 0x0b) || (input->start[0] == 0x0c) || (input->start[0] == 0x0a) || (input->start[0] == 0x0d))
		{
			input->start++;
			input->current++;
			isASpace = 1;
		}

		// Words
		else if (isalpha(input->current[0]) != 0)
		{
			while (isalnum(input->current[0]) != 0)
			{
				input->current++;
			}
			isAWord = 1;
		}

		// Hex
		else if(input->current[0]== '0' && (input->current[1]== 'x' || input->current[1]== 'X') )
		{
			input->current+=2;

			while (isxdigit(input->current[0]) != 0)
			{
				input->current++;
			}
			printf("Hex                 ");
		}

		// Crappy Floating Point
		else if(input->current[0] == '.')
		{
			input->current++;

			while(isdigit(input->current[0]) != 0)
			{
				input->current++;
			}
			printf("Floating Point      ");
		}

		// Octal numbers
		else if(input->current[0]== '0')
		{
			while((isdigit(input->current[0])) != 0 && (input->current[0] != '8') && (input->current[0] != '9'))
			{
				input->current++;
			}
			printf("Octal               ");
		}

		// Integers
		else if(isdigit(input->current[0]) !=0)
		{
			while(isdigit(input->current[0]) != 0)
			{
				input->current++;
			}
			printf("Integer             ");
		}

		//Escape Characters
		else if ((input->current[0] == '\a') ||
				 (input->current[0] == '\b') ||
				 (input->current[0] == '\f') ||
				 (input->current[0] == '\n') ||
				 (input->current[0] == '\r') ||
				 (input->current[0] == '\t') ||
				 (input->current[0] == '\v') ||
				 (input->current[0] == '\\') ||
				 (input->current[0] == '\'') ||
				 (input->current[0] == '\"') ||
				 (input->current[0] == '\?'))
		{
			printf("\033[31mERROR: ESCAPE CHAR [0x%02X]  -->\033[0m", input->current[0]);
			input->current+=2;
		}

		//C Operators
		else if (input->current[0] == '(')
		{
			input->current++;
			printf("Left Parenthesis    ");
		}

		else if (input->current[0] == ')')
		{
			input->current++;
			printf("Right Parenthesis   ");
		}

		else if (input->current[0] == '[')
		{
			input->current++;
			printf("Left Bracket        ");
		}

		else if (input->current[0] == ']')
		{
			input->current++;
			printf("Right Bracket       ");
		}

		else if ((input->current[0] == '-') && (input->current[1] == '>'))
		{
			input->current+=2;
			printf("Structure Pointer   ");
		}

		else if ((input->current[0] == '>') && (input->current[1] == '>') && (input->current[2] == '='))
		{
			input->current+=3;
			printf("Right Shift Assn.   ");
		}

		else if ((input->current[0] == '<') && (input->current[1] == '<') && (input->current[2] == '='))
		{
			input->current+=3;
			printf("Left Shift Assn.    ");
		}

		else if ((input->current[0] == '+') && (input->current[1] == '+'))
		{
			input->current+=2;
			printf("Increment           ");
		}

		else if ((input->current[0] == '-') && (input->current[1] == '-'))
		{
			input->current+=2;
			printf("Decrement           ");
		}

		else if ((input->current[0] == '>') && (input->current[1] == '>'))
		{
			input->current+=2;
			printf("Right Shift         ");
		}

		else if ((input->current[0] == '<') && (input->current[1] == '<'))
		{
			input->current+=2;
			printf("Left Shift          ");
		}

		else if ((input->current[0] == '<') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Less Or Equal       ");
		}

		else if ((input->current[0] == '<') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Greater Or Equal    ");
		}

		else if ((input->current[0] == '=') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Equals              ");
		}

		else if ((input->current[0] == '!') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Not Equals          ");
		}

		else if ((input->current[0] == '&') && (input->current[1] == '&'))
		{
			input->current+=2;
			printf("Logical And         ");
		}

		else if ((input->current[0] == '|') && (input->current[1] == '|'))
		{
			input->current+=2;
			printf("Logical Or          ");
		}

		else if ((input->current[0] == '+') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Plus Equals         ");
		}

		else if ((input->current[0] == '-') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Minus Equals        ");
		}

		else if ((input->current[0] == '*') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Multiply Equals     ");
		}

		else if ((input->current[0] == '/') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Divide Equals       ");
		}

		else if ((input->current[0] == '%') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Modulus Equals      ");
		}

		else if ((input->current[0] == '&') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("And Equals          ");
		}

		else if ((input->current[0] == '^') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Exclusive Or Equals ");
		}

		else if ((input->current[0] == '|') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Inclusive Or Equals ");
		}		

		else if ((input->current[0] == '|') && (input->current[1] == '='))
		{
			input->current+=2;
			printf("Inclusive Or Equals ");
		}

		else if (input->current[0] == '*')
		{
			input->current++;
			printf("Pointer/Multiply    ");
		}
		else if (input->current[0] == '&')
		{
			input->current++;
			printf("Address             ");
		}
		else if (input->current[0] == '-')
		{
			input->current++;
			printf("Minus/Subtract      ");
		}
		else if (input->current[0] == '+')
		{
			input->current++;
			printf("Add                 ");
		}
		else if (input->current[0] == '!')
		{
			input->current++;
			printf("Negate              ");
		}
		else if (input->current[0] == '~')
		{
			input->current++;
			printf("1's complement      ");
		}
		else if (input->current[0] == '/')
		{
			input->current++;
			printf("Divide              ");
		}
		else if (input->current[0] == '%')
		{
			input->current++;
			printf("Modulus             ");
		}
		else if (input->current[0] == '<')
		{
			input->current++;
			printf("Less Than           ");
		}
		else if (input->current[0] == '>')
		{
			input->current++;
			printf("Greater Than        ");
		}
		else if (input->current[0] == '&')
		{
			input->current++;
			printf("Bitwise And         ");
		}
		else if (input->current[0] == '^')
		{
			input->current++;
			printf("Bitwise Ex. Or      ");
		}
		else if (input->current[0] == '|')
		{
			input->current++;
			printf("Bitwise Or          ");
		}
		else if ((input->current[0] == '?') && (input->current[1] == ':'))
		{
			input->current+=2;
			printf("Conditional         ");
		}
		else if (input->current[0] == ',')
		{
			input->current++;
			printf("Comma               ");
		}
		else if (input->current[0] == '=')
		{
			input->current++;
			printf("Equals              ");
		}

		else 
		{
			printf("\n\033[31mPROGRAM EXIT DUE TO ERROR: \"%c\" --> [0x%02X] \n\033[0m", input->current[0], input->current[0]);
			return NULL;
		}

		//Return token to main()
		if (isASpace == 0)
		{
			int length = strlen(input->start) - strlen(input->current);
			input->token = (char*)malloc(sizeof(char)*length+1);

			strncpy(input->token, input->start, length);
			input->token[length] = '\0';

			input->start = input->current;
			
			if (isAWord == 1)
			{
				if (strstr(input->token, "sizeof") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"sizeof\"\033[0m\n");
				if (strstr(input->token, "auto") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"auto\"\033[0m\n");
				if (strstr(input->token, "break") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"break\"\033[0m\n");
				if (strstr(input->token, "case") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"case\"\033[0m\n");
				if (strstr(input->token, "char") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"char\"\033[0m\n");
				if (strstr(input->token, "const") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"const\"\033[0m\n");
				if (strstr(input->token, "continue") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"continue\"\033[0m\n");
				if (strstr(input->token, "default") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"default\"\033[0m\n");
				if (strstr(input->token, "do") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"do\"\033[0m\n");
				if (strstr(input->token, "double") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"double\"\033[0m\n");
				if (strstr(input->token, "else") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"else\"\033[0m\n");
				if (strstr(input->token, "enum") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"enum\"\033[0m\n");
				if (strstr(input->token, "extern") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"extern\"\033[0m\n");
				if (strstr(input->token, "float") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"float\"\033[0m\n");
				if (strstr(input->token, "for") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"for\"\033[0m\n");
				if (strstr(input->token, "goto") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"goto\"\033[0m\n");
				if (strstr(input->token, "if") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"if\"\033[0m\n");
				if (strstr(input->token, "int") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"int\"\033[0m\n");
				if (strstr(input->token, "long") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"long\"\033[0m\n");
				if (strstr(input->token, "register") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"register\"\033[0m\n");
				if (strstr(input->token, "return") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"return\"\033[0m\n");
				if (strstr(input->token, "short") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"short\"\033[0m\n");
				if (strstr(input->token, "signed") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"signed\"\033[0m\n");
				if (strstr(input->token, "static") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"static\"\033[0m\n");
				if (strstr(input->token, "struct") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"struct\"\033[0m\n");
				if (strstr(input->token, "switch") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"switch\"\033[0m\n");
				if (strstr(input->token, "typedef") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"typedef\"\033[0m\n");
				if (strstr(input->token, "union") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"union\"\033[0m\n");
				if (strstr(input->token, "unsigned") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"unsigned\"\033[0m\n");
				if (strstr(input->token, "void") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"void\"\033[0m\n");
				if (strstr(input->token, "volatile") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"volatile\"\033[0m\n");
				if (strstr(input->token, "while") != NULL)
					printf("\033[31mThe token below contains a C Keyword: \"while\"\033[0m\n");
				printf("Word                ");

			}

			return input->token;
		}

		isASpace = 0;
		isAWord = 0;
	}
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
		printf("ERROR: INVALID NUMBER OF ARGUMENTS\n");
		return 1;
	}

	TokenizerT *input = TKCreate(argv[1]);
	char *tokens = " ";

	while (tokens != NULL)
	{
		tokens = TKGetNextToken(input);
		if (tokens != NULL)
			printf("\"%s\"\n", tokens);
	}

	TKDestroy(input);
	return 0;
}