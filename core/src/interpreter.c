#include "../include/interpreter.h"

int interpret(Token* tokens, int numTokens) {
    /*printf("Interpreting:\n");
    printTokens(tokens, numTokens);
    printf("\n\n");*/
    for(int i = 0; i < numTokens; i++) {
        if(tokens[i].tt == IDENTIFIER) {
            i++;
            if(tokens[i].tt == ASSIGN) {
                i++;
                if(tokens[i].tt == NUMBER) {
                    i++;
                    if(tokens[i].tt == SEMICOLON) {
                        printf("Full assignment!!\n");
                    }
                }
            }
        }
        else if(tokens[i].tt == FUNCTION) {
            i++;
            printf("Function definition found!\n");
            printf("Function name: %s\n", tokens[i].value);
            char* fnName = tokens[i].value;
            if(tokens[i].tt == IDENTIFIER) {
                i++;
                if(tokens[i].tt == PARANTHESISLEFT) {
                    i++;
                    if(tokens[i].tt == PARANTHESISRIGHT) {
                        i++;
                        if(tokens[i].tt == BRACKETLEFT) {
                            i++;
                            Token* fntokens = malloc(sizeof(Token) * 8192);
                            int numFunctionTokens = 0;
                            while(tokens[i].tt != BRACKETRIGHT) {
                                fntokens[numFunctionTokens] = tokens[i];
                                i++;
                                numFunctionTokens++;
                            }
                            printf("====================\nParsed %d function tokens for function %s!\n", numFunctionTokens, fnName);
                            printTokens(fntokens, numFunctionTokens);
                            printf("====================\n");
                        }
                    }
                }
            }
        }
    }
}