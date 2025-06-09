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

#define  LOGDEBUG(fmt, ...) { char* dbgmsg = malloc(sizeof(char)*8192); snprintf(dbgmsg, 8192, fmt, __VA_ARGS__); printDebugMessage(DBG, dbgmsg); free(dbgmsg); }
#define  LOGINFO(fmt, ...)  { char* dbgmsg = malloc(sizeof(char)*8192); snprintf(dbgmsg, 8192, fmt, __VA_ARGS__); printDebugMessage(INFO, dbgmsg); free(dbgmsg); }
#define  LOGERROR(fmt, ...) { char* dbgmsg = malloc(sizeof(char)*8192); snprintf(dbgmsg, 8192, fmt, __VA_ARGS__); printDebugMessage(ERR, dbgmsg); free(dbgmsg); }

void printDebugMessage(SlangLogLevel ll, char* message);

void printTokens(Token* tokens, int length);

void printAudioBuffer(double* audioBuffer, int length);

Token getToken(SlangInterpreter* si, int i);

void tokenError(TokenType expected, TokenType got);

void generalError(char* msg);

#ifdef __cplusplus
}
#endif

#endif
