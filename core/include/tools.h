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

#define LOGDEBUG(...) do { \
char* dbgmsg = malloc(8192); \
if (dbgmsg) { \
snprintf(dbgmsg, 8192, __VA_ARGS__); \
printDebugMessage(DBG, dbgmsg); \
free(dbgmsg); \
} \
} while (0)

#define LOGINFO(...) do { \
char* dbgmsg = malloc(8192); \
if (dbgmsg) { \
snprintf(dbgmsg, 8192, __VA_ARGS__); \
printDebugMessage(INFO, dbgmsg); \
free(dbgmsg); \
} \
} while (0)

#define LOGERROR(...) do { \
char* dbgmsg = malloc(8192); \
if (dbgmsg) { \
snprintf(dbgmsg, 8192, __VA_ARGS__); \
printDebugMessage(ERR, dbgmsg); \
free(dbgmsg); \
} \
} while (0)
    
void printDebugMessage(SlangLogLevel ll, char* message);

void printTokens(Token* tokens, int length);

void printAudioBuffer(float* audioBuffer, int length);

Token getToken(SlangInterpreter* si, int i);

void tokenError(TokenType expected, TokenType got);

void generalError(char* msg);

void printAllVariables(SlangInterpreter* si);

void printAllOscillators(SlangInterpreter* si);

void printAllFunctions(SlangInterpreter* si);

float noteNameToFrequency(char *name);

#ifdef __cplusplus
}
#endif

#endif
