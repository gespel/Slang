//
// Created by sten on 11.06.24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef SLANG_TOKENIZER_H
#define SLANG_TOKENIZER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TokenType {
    IDENTIFIER,
    NUMBER,
    FUNCTION,
    SEMICOLON,
    BRACKETLEFT,
    BRACKETRIGHT,
    PARANTHESISLEFT,
    PARANTHESISRIGHT,
    ASSIGN,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    RETURN,
    FOR,
    IF,
    COMMA,
    WHILE,
    SMALLER,
    GREATER,
    SINEOSC,
	TRUESINEOSC,
    SAWOSC,
    WAVEOSC,
    INPUTA,
    INPUTB,
    INPUTC,
    INPUTD,
    NOTEMARKER,
} TokenType;

typedef struct t {
    TokenType tt;
    char* value;
} Token;

Token* tokenize(char* input, int* length);

TokenType checkTokenString(char* input);

char* tokenTypeToString(TokenType input);

void tokenizeStrings(Token* out, int numTokens);

#ifdef __cplusplus
}
#endif

#endif //SLANG_TOKENIZER_H
