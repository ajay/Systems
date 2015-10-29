/*
 * Ajay Srivastava (as1877) & Srihari Chekuri (svc31)
 * simpleTokenizer.h for pa4:Indexer
 */

#ifndef SIMPLETOKENIZER_H
#define SIMPLETOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct TokenizerT;

typedef struct TokenizerT Tokenizer;

Tokenizer *TKCreate(char *originalString);

void TKDestroy(Tokenizer *tk);

char *TKGetNextToken(Tokenizer *input);

#endif