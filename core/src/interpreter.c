#include "../include/interpreter.h"

#ifdef __cplusplus
extern "C" {
#endif

void increase(int* i) {
    (*i)++;
}

int consume(int* i, Token token, TokenType expected) {
#ifdef SLANG_DEBUG
    LOGDEBUG("Consuming %s now. (Expecting %s): %s", tokenTypeToString(token.tt), tokenTypeToString(expected), token.value);
#endif
    if(token.tt == expected) {
        (*i)++;
        return 1;
    }
    else {
        LOGERROR("WRONG TOKEN! EXPECTED \"%s\" GOT \"%s\" INSTEAD (Value: %s)\n", tokenTypeToString(expected), tokenTypeToString(token.tt), token.value);
        exit(-1);
        return 0;
    }
}

void linkInput(SlangInterpreter* si, int nr, double *value) {
    si->inputs[nr] = value;
}

int peek(Token token, TokenType expected) {
    if(token.tt == expected) {
        return 1;
    }
    else {
        LOGERROR("WRONG TOKEN! EXPECTED \"%s\" GOT \"%s\" INSTEAD\n", tokenTypeToString(expected), tokenTypeToString(token.tt));
        exit(-1);
        return 0;
    }
}

void addFunction(SlangInterpreter* si, Function* input) {
    si->functions[si->functions_length] = input;
    si->functions_length++;
}

void printAllFunctions(SlangInterpreter* si) {
#ifdef SLANG_DEBUG
    LOGINFO("=======================================================");
    LOGINFO("Functions:");
    for(size_t i = 0; i < si->functions_length; i++) {
        LOGINFO("functionname: %s", si->functions[i]->name);
        for(size_t j = 0; j < si->functions[i]->function_tokens_length; j++) {
            LOGDEBUG("%s -> %s", tokenTypeToString(si->functions[i]->function_tokens[j].tt), si->functions[i]->function_tokens[j].value);
        }
    }
    LOGINFO("=======================================================");
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
            printDebugMessage(ERR, "OUT OF BOUNDS FOR VARIABLE FETCH");
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
#ifdef SLANG_DEBUG
    LOGINFO("=======================================================");
    LOGINFO("Variables:");
    for(size_t i = 0; i < si->vars_length; i++) {
        LOGINFO("%s: %lf", si->variables[i]->name, si->variables[i]->value);
    }
    LOGINFO("=======================================================");
#endif
}

void printAllOscillators(SlangInterpreter* si) {
#ifdef SLANG_DEBUG
    LOGINFO("=======================================================");
    LOGINFO("Oscillators:");
    for(int i = 0; i < si->main_rack->numSineOscillators; i++) {
        LOGINFO("SineOscillator %s: %lf Hz and %lf volume-multiplier", si->main_rack->sine_oscillators[i]->name, si->main_rack->sine_oscillators[i]->frequency[0], si->main_rack->sine_oscillators[i]->volume);
    }
    for(int i = 0; i < si->main_rack->numWaveOscillators; i++) {
        LOGINFO("WavetableOscillator %s: %lf Hz and %lf volume-multiplier", si->main_rack->wave_oscillators[i]->name, si->main_rack->wave_oscillators[i]->frequency[0], si->main_rack->wave_oscillators[i]->volume);
    }
    LOGINFO("=======================================================");
#endif
}

SlangInterpreter* createSlangInterpreter(Token* tokens, size_t numTokens) {
    SlangInterpreter* out = malloc(sizeof(SlangInterpreter));
    out->tokens = tokens;
    out->numTokens = numTokens;
    out->openBrackets = 0;
    out->last_token_index = 0;
    out->main_rack = malloc(sizeof(Rack));
    out->main_rack->numSineOscillators = 0;
    out->main_rack->sine_oscillators = malloc(sizeof(SineOscillator) * 128);
    out->main_rack->numWaveOscillators = 0;
    out->main_rack->wave_oscillators = malloc(sizeof(WavetableOscillator) * 128);
    return out;
}

void addTokensToInterpreter(SlangInterpreter* si, Token* tokens, size_t numTokens) {
    for(int i = 0; i < numTokens; i++) {
        si->tokens[si->numTokens + i] = tokens[i];
    }
    si->numTokens += numTokens;
}

Function* getFunctionByName(SlangInterpreter* si, char* name) {
    for(size_t i = 0; i < si->functions_length; i++) {
        if(strcmp(si->functions[i]->name, name) == 0) {
            return si->functions[i];
        }
    }
#ifdef SLANG_DEBUG
    LOGDEBUG("Function %s was not found!", name);
#endif
    return NULL;
}

double interpret(SlangInterpreter* si) {
    printDebugMessage(INFO, "Interpreter started!");
    //printAllVariables(si);
    double out = 0.0;
    int numTokens = si->numTokens;
    Token* tokens = si->tokens;

    int i;
    for(i = si->last_token_index; i < numTokens; i++) {
        if(tokens[i].tt == IDENTIFIER || tokens[i].tt == NUMBER) {
            parseExpression(si, &i);
        }
        else if(tokens[i].tt == FUNCTION) {
            parseFunction(si, &i);
        }
        else if(getToken(si, i).tt == RETURN) {
            consume(&i, tokens[i], RETURN);
            double out1 = l3_expression(si, &i);
            #ifdef SLANG_DEBUG
            LOGDEBUG("Returning now! Value: %lf", out1);
            #endif
            return out1;
        }
        else if(getToken(si, i).tt == SEMICOLON) {
            consume(&i, tokens[i], SEMICOLON);
            printDebugMessage(DBG, "Empty line.");
        } 
        else if(getToken(si, i).tt == IF) {
            consume(&i, tokens[i], IF);
            consume(&i, tokens[i], PARANTHESISLEFT);
            double left = l3_expression(si, &i);
            consume(&i, tokens[i], ASSIGN);
            consume(&i, tokens[i], ASSIGN);
            double right = l3_expression(si, &i);

            consume(&i, tokens[i], PARANTHESISRIGHT);
            consume(&i, tokens[i], BRACKETLEFT);
            printDebugMessage(DBG, "IF call found! Evaluating now!");
            if(left == right) {
                printDebugMessage(DBG, "IF is true!");
                si->openBrackets += 1;
            }
            else {
                while(getToken(si, i).tt != BRACKETRIGHT) {
                    inc(&i);
                }
                consume(&i, tokens[i], BRACKETRIGHT);
                printDebugMessage(DBG, "IF is false!");
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
            free(loop_interpreter);
            i = loop_end_index;
        }
        else if(getToken(si, i).tt == BRACKETRIGHT) {
            if((si->openBrackets) > 0) {
                (si->openBrackets)--;
                consume(&i, tokens[i], BRACKETRIGHT);
            }
            else {
                printf("[ERROR] CLOSING BRACKET IS UNEXPECTED! Current openBrackets = %d\n", si->openBrackets);
                exit(-1);
            }
        }
        else if (isOscillator(getToken(si, i))) {
            parseOscillators(si, &i);
        }
        else {
            LOGERROR("Wrong token exception! Type: %s Value: %s", tokenTypeToString(si->tokens[i].tt), si->tokens[i].value);
        }
        i--;
    }
    si->last_token_index = i;
    LOGDEBUG("Last Token Index: %d", si->last_token_index);
    return 0;
}

double terminal(SlangInterpreter* si, int* i) {
    //printDebugMessage(DBG, "Calling terminal:");
    //printDebugMessage(DBG, tokenTypeToString(si->tokens[*i].tt));
    double out;
    switch(si->tokens[*i].tt) {
        case NUMBER:
            out = atof(si->tokens[*i].value);
            inc(i);
            return out;
        case IDENTIFIER:
            if(getFunctionByName(si, si->tokens[*i].value)) {
                Function* f = getFunctionByName(si, si->tokens[*i].value);
                if(f == NULL) {
                    LOGERROR("Function not found!");
                    exit(-1);
                }
                
                consume(i, si->tokens[*i], IDENTIFIER);
                consume(i, si->tokens[*i], PARANTHESISLEFT);
                
                double* arguments = malloc(sizeof(double) * 512);
                int arg_counter = 0;
                
                while(si->tokens[*i].tt != PARANTHESISRIGHT) {
                    
                    arguments[arg_counter] = terminal(si, i);
                    #ifdef SLANG_DEBUG
                    LOGDEBUG("argument: %lf", arguments[arg_counter]);
                    #endif
                    arg_counter++;
                    if(si->tokens[*i].tt != PARANTHESISRIGHT) {
                        consume(i, si->tokens[*i], COMMA);
                    }
                }
                
                if(arg_counter != f->vars_length) {
                    printDebugMessage(ERR, "Number of function call is not equal to function definition!");
                    exit(-1);
                }
                
                consume(i, si->tokens[*i], PARANTHESISRIGHT);

                SlangInterpreter* function_interpreter = malloc(sizeof(SlangInterpreter));
                
                function_interpreter->tokens = f->function_tokens;
                function_interpreter->numTokens = f->function_tokens_length;
                
                for(size_t vi = 0; vi < f->vars_length; vi++) {
                    Variable* nv = malloc(sizeof(Variable));
                    nv->name = f->vars[vi];
                    nv->value = arguments[vi];
                    printDebugMessage(INFO, "Adding variable:");
                    printDebugMessage(INFO, nv->name);
                    addVariable(function_interpreter, nv);
                }
                
                for(size_t function_index = 0; function_index < si->functions_length; function_index++) {
                    function_interpreter->functions[function_index] = si->functions[function_index];
                }
                function_interpreter->functions_length = si->functions_length;
                printAllFunctions(function_interpreter);
                printAllVariables(function_interpreter);
                //exit(-1);
                out = interpret(function_interpreter);
                free(function_interpreter);
                //printAllVariables(function_interpreter);
                //printAllFunctions(function_interpreter);
                return out;
            }
            else {
                Variable* tvar = getVariableByName(si, si->tokens[*i].value);
                if(tvar == NULL) {
                    LOGERROR("%s Variable is unkown!", si->tokens[*i].value);
                    exit(-1);
                }
                out = tvar->value;
                inc(i);
            }
            return out;
        default:
            generalError("Terminal expected NUMBER or IDENTIFIER");
            exit(-1);
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
        default:
            break;
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
        default:
            break;
    }
    return left;
}

double l1_expression(SlangInterpreter* si, int* i) {
    printDebugMessage(DBG, "Called expression");
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

char* getInterpreterStatusString(SlangInterpreter* si) {
    char* out = calloc(8192, sizeof(char));

    for (int i = 0; i < si->numTokens; i++) {
        char* tbuf = malloc(32 * sizeof(char));
        snprintf(tbuf, 32, "%s -> %s\n", tokenTypeToString(si->tokens[i].tt), si->tokens[i].value);
        strcat(out, tbuf);
    }

    return out;
}

int isOscillator(Token token) {
    if (token.tt == SEMICOLON || token.tt == SAWOSC || token.tt == TRUESINEOSC || token.tt == WAVEOSC || token.tt == SINEOSC) {
        return 1;
    }
    return 0;
}

int getInputIndex(Token token) {
    if (token.tt == INPUTA) {
        return 0;
    }
    if (token.tt == INPUTB) {
        return 1;
    }
    if (token.tt == INPUTC) {
        return 2;
    }
    if (token.tt == INPUTD) {
        return 3;
    }
    return -1;
}


#ifdef __cplusplus
}
#endif
