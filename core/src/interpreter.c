#include "../include/interpreter.h"

#ifdef __cplusplus
extern "C" {
#endif

void increase(int* i) {
    (*i)++;
}

int consume(int* i, Token token, TokenType expected) {
#ifdef DEBUG
    char* dbgmsg = malloc(sizeof(char)*1024);
    snprintf(dbgmsg, 1024, "Consuming %s now. (Expecting %s): %s", tokenTypeToString(token.tt), tokenTypeToString(expected), token.value);
    printDebugMessage(dbgmsg);
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
    printDebugMessage("=======================================================");
    for(size_t i = 0; i < si->functions_length; i++) {
        printDebugMessage("functionname:");
        printDebugMessage(si->functions[i]->name);
        for(size_t j = 0; j < si->functions[i]->function_tokens_length; j++) {
            char* dbgmsg = malloc(sizeof(char)*1024);
            snprintf(dbgmsg, 1024, "%s -> %s", tokenTypeToString(si->functions[i]->function_tokens[j].tt), si->functions[i]->function_tokens[j].value);
            printDebugMessage(dbgmsg);
        }
    }
    printDebugMessage("=======================================================");
#endif
}

void addVariable(SlangInterpreter* input_inter, Variable* input) {
    input_inter->variables[input_inter->vars_length] = input;
    input_inter->vars_length++;
}

void removeVariable(SlangInterpreter* si, char* name) {
    //TODO!
}

Variable* getVariableByName(SlangInterpreter* si, char* name) {
    for(size_t variableIndex = 0; variableIndex < si->vars_length; variableIndex++) {
        if(si->variables[variableIndex] == NULL) {
            printf("%d", variableIndex);
            printDebugMessage("ERROR OUT OF BOUNDS FOR VARIABLE FETCH");
            exit(1);
        }
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
    printDebugMessage("Variables:");
    for(size_t i = 0; i < si->vars_length; i++) {
        char* dbgmsg = malloc(sizeof(char)*1024);
        snprintf(dbgmsg, 1024, "%s: %lf", si->variables[i]->name, si->variables[i]->value);
        printDebugMessage(dbgmsg);
    }
#endif
}

SlangInterpreter* createSlangInterpreter(Token* tokens, size_t numTokens) {
    SlangInterpreter* out = malloc(sizeof(SlangInterpreter));
    out->tokens = tokens;
    out->numTokens = numTokens;
    out->openBrackets = 0;
    return out;
}

Function* getFunctionByName(SlangInterpreter* si, char* name) {
    for(size_t i = 0; i < si->functions_length; i++) {
        if(strcmp(si->functions[i]->name, name) == 0) {
            return si->functions[i];
        }
    }
#ifdef DEBUG
    char* dbgmsg = malloc(sizeof(char)*1024);
    snprintf(dbgmsg, 1024, "Function %s was not found!", name);
    printDebugMessage(dbgmsg);
#endif
    return NULL;
}

double interpret(SlangInterpreter* si) {
    printDebugMessage("INTERPRETER STARTED!");
    printAllVariables(si);
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
                
                if(getVariableByName(si, name) != NULL) {
                    getVariableByName(si, name)->value = var_value;
                }
                else {
                    Variable* temp_var = malloc(sizeof(Variable));
                    temp_var->name = name;
                    temp_var->value = var_value;

                    addVariable(si, temp_var);
                }
                
                //inc(&i);
            }
            else if(tokens[i].tt == PARANTHESISLEFT) {
                printDebugMessage("Function call!");
                consume(&i, tokens[i], PARANTHESISLEFT);
                consume(&i, tokens[i], PARANTHESISRIGHT);
                //peek(tokens[i], SEMICOLON);

                Function* f = getFunctionByName(si, name);

                if(f) {
                    #ifdef DEBUG
                    char* dbgmsg = malloc(sizeof(char)*1024);
                    snprintf(dbgmsg, 1024, "Calling function %s now!", name);
                    printDebugMessage(dbgmsg);
                    #endif
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
            #ifdef DEBUG
            char* dbgmsg = malloc(sizeof(char)*1024);
            snprintf(dbgmsg, 1024, "Returning now! Value: %lf", out);
            printDebugMessage(dbgmsg);
            #endif
            return out;
        }
        else if(getToken(si, i).tt == SEMICOLON) {
            consume(&i, tokens[i], SEMICOLON);
            printDebugMessage("Empty line.");
        } 
        else if(getToken(si, i).tt == IF) {
            consume(&i, tokens[i], IF);
            consume(&i, tokens[i], PARANTHESISLEFT);
            double left = terminal(si, &i);
            consume(&i, tokens[i], ASSIGN);
            consume(&i, tokens[i], ASSIGN);
            double right = terminal(si, &i);

            consume(&i, tokens[i], PARANTHESISRIGHT);
            consume(&i, tokens[i], BRACKETLEFT);
            printDebugMessage("IF call found! Evaluating now!");
            if(left == right) {
                printDebugMessage("IF is true!");
                si->openBrackets += 1;
            }
            else {
                while(getToken(si, i).tt != BRACKETRIGHT) {
                    inc(&i);
                }
                consume(&i, tokens[i], BRACKETRIGHT);
                printDebugMessage("IF is false!");
            } 
        }
        else if(getToken(si, i).tt == WHILE) {
            consume(&i, tokens[i], WHILE);
            consume(&i, tokens[i], PARANTHESISLEFT);
            char* run_var_name = getToken(si, i).value;
            consume(&i, tokens[i], IDENTIFIER);
            consume(&i, tokens[i], ASSIGN);
            double run_var_assign = terminal(si, &i);

            Variable* running_var = malloc(sizeof(Variable));
            running_var->name = run_var_name;
            running_var->value = run_var_assign;
            consume(&i, tokens[i], COMMA);
            
            char* logic_var_left_name = getToken(si, i).value;
            consume(&i, tokens[i], IDENTIFIER);

            char* logic_operator = getToken(si, i).value;
            inc(&i);
            
            double logic_static_right = terminal(si, &i);
            consume(&i, tokens[i], COMMA);
           
            int mod_index = i;
            while(getToken(si, i).tt != PARANTHESISRIGHT) {
                inc(&i);
            }
            consume(&i, tokens[i], PARANTHESISRIGHT);

            /*char dbgmsg[1024];
            snprintf(dbgmsg, 1024, "Full FOR definition found: var: %s = %lf, logic: %s %s %lf, modindex: %d", running_var->name, running_var->value, logic_var_left->name, logic_operator, logic_static_right, mod_index);
            printDebugMessage(dbgmsg);*/
            consume(&i, tokens[i], BRACKETLEFT);
            int other_brackets = -1;
            Token* loop_tokens = malloc(sizeof(Token)*1024);
            int loop_tokens_index = 0;
            
            while(getToken(si, i).tt != BRACKETRIGHT && other_brackets != 0) {
                if(getToken(si, i).tt == BRACKETLEFT) {
                    other_brackets++;
                }
                if(getToken(si, i).tt == BRACKETRIGHT) {
                    other_brackets--;
                }
                loop_tokens[loop_tokens_index] = getToken(si, i);
                loop_tokens_index++;
                inc(&i);
            }
            consume(&i, tokens[i], BRACKETRIGHT);
            int loop_end_index = i;
            
            SlangInterpreter* loop_interpreter = malloc(sizeof(SlangInterpreter));
            loop_interpreter->tokens = loop_tokens;
            loop_interpreter->numTokens = loop_tokens_index;

            for(size_t variable_index = 0; variable_index < si->vars_length; variable_index++) {
                addVariable(loop_interpreter, si->variables[variable_index]);
            }
            addVariable(loop_interpreter, running_var);
            addVariable(si, running_var);
            Variable* logic_var_left = getVariableByName(loop_interpreter, logic_var_left_name);
            
            for(size_t function_index = 0; function_index < si->functions_length; function_index++) {
                loop_interpreter->functions[function_index] = si->functions[function_index];
            }
            loop_interpreter->functions_length = si->functions_length;
            
            if(*logic_operator == '<') {
                while(logic_var_left->value < logic_static_right) {
                    interpret(loop_interpreter);
                    i = mod_index;
                    logic_var_left->value = l3_expression(si, &i);
                }
            }
            else if(*logic_operator == '>') {
                while(logic_var_left->value > logic_static_right) {
                    interpret(loop_interpreter);
                    i = mod_index;
                    logic_var_left->value = l3_expression(si, &i);
                }
            }
            else if(*logic_operator == '=') {
                while(logic_var_left->value == logic_static_right) {
                    interpret(loop_interpreter);
                    i = mod_index;
                    logic_var_left->value = l3_expression(si, &i);
                }
            }
            i = loop_end_index;
        }
        else if(getToken(si, i).tt == BRACKETRIGHT) {
            if((si->openBrackets) > 0) {
                (si->openBrackets)--;
                consume(&i, tokens[i], BRACKETRIGHT);
            }
            else {
                printf("[ERROR] CLOSING BRACKET IS UNEXPECTED! Current openBrackets = %ld\n", si->openBrackets);
                exit(-1);
            }
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
                    double arg = terminal(si, i);
                    #ifdef DEBUG
                    char* dbgmsg = malloc(sizeof(char)*1024);
                    snprintf(dbgmsg, 1024, "argument: %lf", arg);
                    printDebugMessage(dbgmsg);
                    #endif
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
                //printAllVariables(function_interpreter);
                //printAllFunctions(function_interpreter);
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

#ifdef __cplusplus
}
#endif
