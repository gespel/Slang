#include "../include/interpreter.h"

int interpret(Token* tokens, int numTokens) {
    /*printf("Interpreting:\n");
    printTokens(tokens, numTokens);
    printf("\n\n");*/
    for(int i = 0; i < numTokens; i++) {
        if(tokens[i].tt == IDENTIFIER) {
            char* var_name = tokens[i].value;
            consume(&i, tokens[i], IDENTIFIER);
            consume(&i, tokens[i], ASSIGN);
            peek(tokens[i], NUMBER);

            double var_value;
            sscanf(tokens[i].value, "%lf", &var_value);

            Variable* temp_var = malloc(sizeof(Variable));
            temp_var->name = var_name;
            temp_var->value = var_value;

            addVariable(temp_var);

            consume(&i, tokens[i], NUMBER);
            //consume(&i, tokens[i], SEMICOLON);
        }
        else if(tokens[i].tt == FUNCTION) {
            consume(&i, tokens[i], FUNCTION);
#ifdef DEBUG
                printf("[DEBUG] Function definition found!\n");
#endif
            
            char* fnName = NULL;

            if(peek(tokens[i], IDENTIFIER)) {
#ifdef DEBUG
                    printf("[DEBUG] Function name: %s\n", tokens[i].value);
#endif
                fnName = tokens[i].value;
            }
            
            consume(&i, tokens[i], IDENTIFIER);
            consume(&i, tokens[i], PARANTHESISLEFT);
            consume(&i, tokens[i], PARANTHESISRIGHT);
            consume(&i, tokens[i], BRACKETLEFT);

            Token* fntokens = malloc(sizeof(Token) * 8192);
            int numFunctionTokens = 0;

            while(tokens[i].tt != BRACKETRIGHT) {
                fntokens[numFunctionTokens] = tokens[i];
                i++;
                numFunctionTokens++;
            }

            Function* temp = malloc(sizeof(Function));
            temp->name = fnName;
            temp->function_tokens = fntokens;
            temp->function_tokens_length = numFunctionTokens;

            addFunction(temp);
        }
    }
    return 1;
}
