#include "../include/tools.h"

void printDebugMessage(char* message) {
#ifdef DEBUG
    char buffer[30];
    struct timeval tv;
    time_t curtime;
    gettimeofday(&tv, NULL); 
    curtime=tv.tv_sec;
    strftime(buffer,30,"%m-%d-%Y  %T.", localtime(&curtime));
    printf("\033[95m%s\033[0m - \033[92mDEBUG\033[0m: \033[96m%s\033[0m\n", buffer, message);
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

void generalError(char* msg) {
    printf("[ERROR] %s", msg);
    exit(1);
}
