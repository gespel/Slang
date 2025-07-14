#include "../include/tools.h"

void printDebugMessage(SlangLogLevel ll, char* message) {
#ifdef SLANG_DEBUG
    char buffer[30];
    struct timeval tv;
    time_t curtime;
    gettimeofday(&tv, NULL); 
    curtime = tv.tv_sec;
    strftime(buffer,30,"%d-%m-%Y %T", localtime(&curtime));

    char* prefix = malloc(sizeof(char)*16);
    switch (ll) {
        case DBG: prefix = "\033[95mDEBUG\033[0m"; break;
        case INFO: prefix = "\033[92mINFO\033[0m"; break;
        case WARN: prefix = "\033[93mWARNING\033[0m"; break;
        case ERR: prefix = "\033[91mERROR\033[0m"; break;
    }

    printf("[Slang] \033[34m%s\033[0m - %s: %s\n", buffer, prefix, message);
#endif
}

void printTokens(Token* tokens, int length) {
    for(int j = 0; j < length; j++) {
        printf("%s with value %s\n", tokenTypeToString(tokens[j].tt), tokens[j].value);
    }
}

void printAudioBuffer(double* audioBuffer, int length) {
    for(int j = 0; j < length; j++) {
        if (audioBuffer[j]) {
            printf("\t%d: %lf ", j, audioBuffer[j]);
        }
        if ((j+1) % 8 == 0) {
            printf("\n");
        }
    }
}


Token getToken(SlangInterpreter* si, int i) {
    return si->tokens[i];
}

void tokenError(TokenType expected, TokenType got) {
    printf("Unexpected token! Expected '%s' but got '%s'\n", tokenTypeToString(expected), tokenTypeToString(got));
    exit(1);
}

void generalError(char* msg) {
    printf("[ERROR] %s", msg);
    exit(1);
}
