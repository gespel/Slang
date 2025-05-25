#ifndef SLANG_TOOLS_H
#define SLANG_TOOLS_H
#include <stdio.h>
#include "tokenizer.h"
#include "interpreter.h"
#include <sys/time.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SlangLogLevel {
    DBG,
    INFO,
    WARN,
    ERR,
} SlangLogLevel;

void printDebugMessage(SlangLogLevel ll, char* message);

void printTokens(Token* tokens, int length);

Token getToken(SlangInterpreter* si, int i);

void tokenError(TokenType expected, TokenType got);

void generalError(char* msg);

#ifdef __cplusplus
}
#endif

#endif
