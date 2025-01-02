#ifndef SLANG_TOOLS_H
#define SLANG_TOOLS_H
#include <stdio.h>
#include "tokenizer.h"
#include "interpreter.h"

void printDebugMessage(char* message) {
#ifdef DEBUG
    printf("[DEBUG] %s\n", message);
#endif
}

void printTokens(Token* tokens, int length) {
    for(int j = 0; j < length; j++) {
        printf("%s with value %s\n", tokenTypeToString(tokens[j].tt), tokens[j].value);
    }
}

Token getToken(SlangInterpreter* si, int i) {
    return si->tokens[i];
}

void tokenError(TokenType expected, TokenType got) {
    printf("Unexpected token! Expected '%s' but got '%s'\n", tokenTypeToString(expected), tokenTypeToString(got));
    exit(1);
}

#endif
