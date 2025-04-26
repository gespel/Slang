#include "../include/interpreter.h"

void increase(int* i) {
    (*i)++;
}

int consume(int* i, Token token, TokenType expected) {
#ifdef DEBUG
    printf("[DEBUG] Consuming %s now. (Expecting %s): %s\n", tokenTypeToString(token.tt), tokenTypeToString(expected), token.value);
#endif
    if(token.tt == expected) {
        (*i)++;
        return 1;
    }
    else {
        printf("\n[ERROR] WRONG TOKEN! EXPECTED \"%s\" GOT \"%s\" INSTEAD (Value: %s)\n", tokenTypeToString(expected), tokenTypeToString(token.tt), token.value);
        exit(-1);
        return 0;
    }
}

int peek(Token token, TokenType expected) {
    if(token.tt == expected) {
        return 1;
    }
    else {
        printf("\nERROR! WRONG TOKEN! EXPECTED \"%s\" GOT \"%s\" INSTEAD\n", tokenTypeToString(expected), tokenTypeToString(token.tt));
        exit(-1);
        return 0;
    }
}

void addFunction(SlangInterpreter* si, Function* input) {
    si->functions[si->functions_length] = input;
    si->functions_length++;
}

void printAllFunctions(SlangInterpreter* si) {
#ifdef DEBUG
    printf("[DEBUG] =======================================================\n");
    for(size_t i = 0; i < si->functions_length; i++) {
        printf("[DEBUG] functionname: %s\n", si->functions[i]->name);
        for(size_t j = 0; j < si->functions[i]->function_tokens_length; j++) {
            printf("[DEBUG] \t%s -> %s\n", tokenTypeToString(si->functions[i]->function_tokens[j].tt), si->functions[i]->function_tokens[j].value);
        }
    }
    printf("[DEBUG] =======================================================\n");
#endif
}

void addVariable(SlangInterpreter* si, Variable* input) {
    si->variables[si->vars_length] = input;
    si->vars_length++;
}

Variable* getVariableByName(SlangInterpreter* si, char* name) {
    for(size_t variableIndex = 0; variableIndex < si->vars_length; variableIndex++) {
        if(strcmp(si->variables[variableIndex]->name, name) == 0) {
            return si->variables[variableIndex];
        }
    }
    return NULL;
}

void inc(int* i) {
    (*i)++;
}

void dec(int* i) {
    (*i)--;
}

void printAllVariables(SlangInterpreter* si) {
#ifdef DEBUG
    printf("[DEBUG] =======================================================\n");
    printf("[DEBUG] Variables:\n");
    for(size_t i = 0; i < si->vars_length; i++) {
        printf("[DEBUG] %s: %lf\n", si->variables[i]->name, si->variables[i]->value);
    }
    printf("[DEBUG] =======================================================\n");
#endif
}

SlangInterpreter* createSlangInterpreter(Token* tokens, size_t numTokens) {
    SlangInterpreter* out = malloc(sizeof(SlangInterpreter));
    out->tokens = tokens;
    out->numTokens = numTokens;
    return out;
}

Function* getFunctionByName(SlangInterpreter* si, char* name) {
    for(size_t i = 0; i < si->functions_length; i++) {
        if(strcmp(si->functions[i]->name, name) == 0) {
            return si->functions[i];
        }
    }
#ifdef DEBUG
    printf("[DEBUG] Function %s was not found!\n", name);
#endif
    return NULL;
}

double interpret(SlangInterpreter* si) {
    double out = 0.0;
    int numTokens = si->numTokens;
    Token* tokens = si->tokens;

    for(int i = 0; i < numTokens; i++) {
        if(tokens[i].tt == IDENTIFIER) {
            char* name = tokens[i].value;
            consume(&i, tokens[i], IDENTIFIER);
            if(tokens[i].tt == ASSIGN) {
                consume(&i, tokens[i], ASSIGN);
                //peek(tokens[i], NUMBER);
                double var_value = l3_expression(si, &i);

                Variable* temp_var = malloc(sizeof(Variable));
                temp_var->name = name;
                temp_var->value = var_value;

                addVariable(si, temp_var);
                //inc(&i);
            }
            else if(tokens[i].tt == PARANTHESISLEFT) {
                printDebugMessage("Function call!");
                consume(&i, tokens[i], PARANTHESISLEFT);
                consume(&i, tokens[i], PARANTHESISRIGHT);
                //peek(tokens[i], SEMICOLON);

                Function* f = getFunctionByName(si, name);

                if(f) {
                    printf("[DEBUG] Calling function %s now!\n", name);
                    SlangInterpreter* function_interpreter = malloc(sizeof(SlangInterpreter));
                    
                    function_interpreter->tokens = f->function_tokens;
                    function_interpreter->numTokens = f->function_tokens_length;

                    for(size_t variable_index = 0; variable_index < si->vars_length; variable_index++) {
                        function_interpreter->variables[variable_index] = si->variables[variable_index];
                    }
                    function_interpreter->vars_length = si->vars_length;

                    for(size_t function_index = 0; function_index < si->functions_length; function_index++) {
                        function_interpreter->functions[function_index] = si->functions[function_index];
                    }
                    function_interpreter->functions_length = si->functions_length;

                    interpret(function_interpreter);
                    printAllVariables(function_interpreter);
                    printAllFunctions(function_interpreter);
                    //interpret(f->function_tokens, f->function_tokens_length);
                }
                else {
                    printf("[ERROR] Function not found! Exiting...\n");
                    exit(-1);
                }
            }  
            consume(&i, tokens[i], SEMICOLON);
        }
        else if(tokens[i].tt == FUNCTION) {
            consume(&i, tokens[i], FUNCTION);
            printDebugMessage("Function definition found!");
            
            char* fnName = NULL;

            if(peek(tokens[i], IDENTIFIER)) {
                printDebugMessage("Function name:");
                printDebugMessage(tokens[i].value);
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
                inc(&i);
                numFunctionTokens++;
            }

            addFunction(si, createFunction(fnName, fntokens, numFunctionTokens));
            consume(&i, tokens[i], BRACKETRIGHT);
        }
        else if(getToken(si, i).tt == RETURN) {
            consume(&i, tokens[i], RETURN);
            double out = l3_expression(si, &i);
            printDebugMessage("Returning now! Value:");
            printf("[DEBUG] %lf\n", out);
            return out;
        }
        else if(getToken(si, i).tt == SEMICOLON) {
            consume(&i, tokens[i], SEMICOLON);
            printDebugMessage("Empty line.");
        } 
        else if(getToken(si, i).tt == IF) {
            consume(&i, tokens[i], IF);
            consume(&i, tokens[i], PARANTHESISLEFT);
            Token* logicTokens = malloc(sizeof(Token)*1024);
            int numLogicTokens = 0;
            while(getToken(si, i).tt != PARANTHESISRIGHT) {
                logicTokens[numLogicTokens] = getToken(si, i);
                inc(&i);
                numLogicTokens++;
            }
            consume(&i, tokens[i], PARANTHESISRIGHT);
            consume(&i, tokens[i], BRACKETLEFT);
            printDebugMessage("IF call found! Evaluating now!");
        }
        else {
            printf("[ERROR] Wrong token exception! Type: %s Value: %s\n", tokenTypeToString(si->tokens[i].tt), si->tokens[i].value);
        }
        i--;
    }
    return 0;
}

double terminal(SlangInterpreter* si, int* i) {
    printDebugMessage("Calling terminal:");
    printDebugMessage(tokenTypeToString(si->tokens[*i].tt));
    double out;
    switch(si->tokens[*i].tt) {
        case NUMBER:
            out = atof(si->tokens[*i].value);
            inc(i);
            return out;
        case IDENTIFIER:
            if(getFunctionByName(si, si->tokens[*i].value)) {
                Function* f = getFunctionByName(si, si->tokens[*i].value);
                consume(i, si->tokens[*i], IDENTIFIER);
                consume(i, si->tokens[*i], PARANTHESISLEFT);
                
                Token* arguments = malloc(sizeof(Token) * 512);
                int arg_counter = 0;

                while(si->tokens[*i].tt != PARANTHESISRIGHT) {    
                    printf("[DEBUG] argument: %lf\n", terminal(si, i));
                    arg_counter++;
                    if(si->tokens[*i].tt != PARANTHESISRIGHT) {
                        consume(i, si->tokens[*i], COMMA);
                    }
                }
                consume(i, si->tokens[*i], PARANTHESISRIGHT);

                for(int ac = 0; ac < arg_counter; ac++) {
                    
                }

                SlangInterpreter* function_interpreter = malloc(sizeof(SlangInterpreter));

                function_interpreter->tokens = f->function_tokens;
                function_interpreter->numTokens = f->function_tokens_length;
 
                for(size_t variable_index = 0; variable_index < si->vars_length; variable_index++) {
                    function_interpreter->variables[variable_index] = si->variables[variable_index];
                }
                function_interpreter->vars_length = si->vars_length;

                for(size_t function_index = 0; function_index < si->functions_length; function_index++) {
                    function_interpreter->functions[function_index] = si->functions[function_index];
                }
                function_interpreter->functions_length = si->functions_length;
                out = interpret(function_interpreter);
                printAllVariables(function_interpreter);
                printAllFunctions(function_interpreter);
                return out;
            }
            else {
                out = getVariableByName(si, si->tokens[*i].value)->value;
                inc(i);
            }
            return out;
        default:
            generalError("Terminal expected NUMBER or IDENTIFIER");
    }
}

double l3_expression(SlangInterpreter* si, int* i) {
    double left = l2_expression(si, i);
    double right;

    switch(getToken(si, *i).tt) {
        case PLUS:
            consume(i, si->tokens[*i], PLUS);
            right = l3_expression(si, i);
            return left + right;
        case MINUS:
            consume(i, si->tokens[*i], MINUS);
            right = l3_expression(si, i);
            return left - right; 
    }
    return left;
}

double l2_expression(SlangInterpreter* si, int* i) {
    double left, right;
    left = l1_expression(si, i);

    switch(getToken(si, *i).tt) {
        case MULTIPLY:
            consume(i, si->tokens[*i], MULTIPLY);
            right = l3_expression(si, i);
            return left * right;
        case DIVIDE:
            consume(i, si->tokens[*i], DIVIDE);
            right = l3_expression(si, i);
            return left / right;
    }
    return left;
}

double l1_expression(SlangInterpreter* si, int* i) {
    printDebugMessage("Called expression");
    //printDebugMessage(tokenTypeToString(s->tokens[*i].tt));
    //printDebugMessage(s->tokens[*i].value);
    double left, right;
    if(si->tokens[*i].tt == PARANTHESISLEFT) {
        //printDebugMessage("Hit parantheses!");
        consume(i, si->tokens[*i], PARANTHESISLEFT);
        left = l3_expression(si, i);
        consume(i, si->tokens[*i], PARANTHESISRIGHT); 
    }
    else {
        //printDebugMessage("No parantheses. Regular left...");
        left = terminal(si, i);
    }
    return left;
}

