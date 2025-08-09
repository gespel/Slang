//
// Created by sten on 11.06.24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef SLANG_TOKENIZER_H
#define SLANG_TOKENIZER_H
#include "core_types.h"

#ifdef __cplusplus
extern "C" {
#endif



Token* tokenize(char* input, int* length);

TokenType checkTokenString(char* input);

char* tokenTypeToString(TokenType input);

void tokenizeStrings(Token* out, int numTokens);

#ifdef __cplusplus
}
#endif

#endif //SLANG_TOKENIZER_H
