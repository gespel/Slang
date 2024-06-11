//
// Created by sten on 11.06.24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef SLANG_CORE_H
#define SLANG_CORE_H

typedef enum TokenType {
  IDENTIFIER,
  NUMBER,
  FUNCTION,
  SEMICOLON,
} TokenType;

typedef struct t {
    TokenType tt;
    char* value;
} Token;

Token* tokenize(char* input, int* length);

TokenType checkTokenString(char* input);

char* tokenTypeToString(TokenType input);


#endif //SLANG_CORE_H
