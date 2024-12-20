#include "../include/interpreter.h"

int interpret(Token* tokens, int numTokens) {
    /*printf("Interpreting:\n");
    printTokens(tokens, numTokens);
    printf("\n\n");*/
    for(int i = 0; i < numTokens; i++) {
        if(tokens[i].tt == IDENTIFIER) {
            char* var_name = tokens[i].value;
            i++;
            if(tokens[i].tt == ASSIGN) {
                i++;
                if(tokens[i].tt == NUMBER) {
                    double var_value;
                    sscanf(tokens[i].value, "%lf", &var_value);
                    Variable temp_var = {
                        .name = var_name,
                        .value = var_value
                    };
                    addVariable(temp_var);
                    i++;
                    if(tokens[i].tt == SEMICOLON) {
                        printf("Full assignment!!\n");
                    }
                    else {
                        tokenError(SEMICOLON, tokens[i].tt);
                    }
                }
                else {
                    tokenError(NUMBER, tokens[i].tt);
                }
            }
            else {
                tokenError(ASSIGN, tokens[i].tt);
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
                            //printf("====================\nParsed %d function tokens for function %s!\n", numFunctionTokens, fnName);
                            //printTokens(fntokens, numFunctionTokens);
                            Function temp = {
                                .name = fnName,
                                .function_tokens = fntokens,
                                .function_tokens_length = numFunctionTokens
                            };
                            addFunction(temp);
                            //printf("====================\n");
                        }
                        else {
                            tokenError(BRACKETLEFT, tokens[i].tt);
                        }
                    }
                    else {
                        tokenError(PARANTHESISRIGHT, tokens[i].tt);
                    }
                }
                else {
                    tokenError(PARANTHESISLEFT, tokens[i].tt);
                }
            }
            else {
                tokenError(IDENTIFIER, tokens[i].tt);
            }
        }
    }
}
