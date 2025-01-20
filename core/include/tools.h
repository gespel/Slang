#ifndef SLANG_TOOLS_H
#define SLANG_TOOLS_H
#include <stdio.h>
#include "tokenizer.h"
#include "interpreter.h"

void printDebugMessage(char* message);

void printTokens(Token* tokens, int length);

Token getToken(SlangInterpreter* si, int i);

void tokenError(TokenType expected, TokenType got);

void generalError(char* msg);

#endif
