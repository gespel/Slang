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

void linkInput(SlangInterpreter* si, int nr, float *value) {
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

SlangInterpreter* createSlangInterpreter(Token* tokens, size_t numTokens) {
    SlangInterpreter* out = malloc(sizeof(SlangInterpreter));
    out->tokens = tokens;
    out->numTokens = numTokens;
    out->openBrackets = 0;
    out->last_token_index = 0;
    out->main_rack = malloc(sizeof(Rack));
    out->main_rack->oscillators = malloc(sizeof(Oscillator) * 128);
    out->main_rack->numOscillators = 0;
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

float interpret(SlangInterpreter* si) {
    printDebugMessage(INFO, "Interpreter started!");
    //printAllVariables(si);
    float out = 0.0;
    int numTokens = si->numTokens;
    Token* tokens = si->tokens;

    int i;
    for(i = si->last_token_index; i < numTokens; i++) {
        if(tokens[i].tt == IDENTIFIER) {
            parseExpression(si, &i);
        }
        else if (tokens[i].tt == NUMBER) {
            parseExpression(si, &i);
        }
        else if(tokens[i].tt == FUNCTION) {
            parseFunction(si, &i);
        }
        else if(getToken(si, i).tt == RETURN) {
            consume(&i, tokens[i], RETURN);
            float out1 = l3_expression(si, &i);
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

            printDebugMessage(DBG, "IF call found! Evaluating now!");

        	int l = checkLogic(si, &i);

            consume(&i, tokens[i], PARANTHESISRIGHT);
            consume(&i, tokens[i], BRACKETLEFT);
            int nrbr = si->openBrackets;
            si->openBrackets++;
            if (l == 0) {
                while (si->openBrackets > nrbr) {
                    if (getToken(si, i).tt == BRACKETRIGHT) {
                        si->openBrackets--;
                    }
                    i++;
                }
            }
        }
        else if(getToken(si, i).tt == WHILE) {
            consume(&i, tokens[i], WHILE);
            consume(&i, tokens[i], PARANTHESISLEFT);
            char* run_var_name = getToken(si, i).value;
            consume(&i, tokens[i], IDENTIFIER);
            consume(&i, tokens[i], ASSIGN);
            float run_var_assign = terminal(si, &i);

            Variable* running_var = malloc(sizeof(Variable));
            running_var->name = run_var_name;
            running_var->value = run_var_assign;
            consume(&i, tokens[i], COMMA);
            
            char* logic_var_left_name = getToken(si, i).value;
            consume(&i, tokens[i], IDENTIFIER);

            char* logic_operator = getToken(si, i).value;
            inc(&i);
            
            float logic_static_right = terminal(si, &i);
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
            parseOscillators(si, &i, NULL);
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

float terminal(SlangInterpreter* si, int* i) {
    //printDebugMessage(DBG, "Calling terminal:");
    //printDebugMessage(DBG, tokenTypeToString(si->tokens[*i].tt));
    float out;
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
                
                float* arguments = malloc(sizeof(float) * 512);
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

                /*SlangInterpreter* function_interpreter = malloc(sizeof(SlangInterpreter));
                
                function_interpreter->tokens = f->function_tokens;
                function_interpreter->numTokens = f->function_tokens_length;*/

				SlangInterpreter *function_interpreter = createSlangInterpreter(f->function_tokens, f->function_tokens_length);
                
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
        case NOTEMARKER:
            consume(i, si->tokens[*i], NOTEMARKER);
            out = noteNameToFrequency(si->tokens[*i].value);
            consume(i, si->tokens[*i], IDENTIFIER);
            return out;
        case INPUTA:
            out = si->inputs[0][0];
            return out;
        case INPUTB:
            out = si->inputs[1][0];
            return out;
        case INPUTC:
            out = si->inputs[2][0];
            return out;
        case INPUTD:
            out = si->inputs[3][0];
            return out;
        default:
            generalError("Terminal expected NUMBER or IDENTIFIER");
            exit(-1);
    }

}

float l3_expression(SlangInterpreter* si, int* i) {
    float left = l2_expression(si, i);
    float right;

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

float l2_expression(SlangInterpreter* si, int* i) {
    float left, right;
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

float l1_expression(SlangInterpreter* si, int* i) {
    printDebugMessage(DBG, "Called expression");
    //printDebugMessage(tokenTypeToString(s->tokens[*i].tt));
    //printDebugMessage(s->tokens[*i].value);
    float left, right;
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
    if (token.tt == SEMICOLON || token.tt == SAWOSC || token.tt == TRUESINEOSC || token.tt == WAVEOSC || token.tt == SINEOSC || token.tt == SQUAREOSC) {
        return 1;
    }
    return 0;
}

int isInput(Token token) {
    if (token.tt == INPUTA || token.tt == INPUTB || token.tt == INPUTC || token.tt == INPUTD) {
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

void setInput(SlangInterpreter* si, int index, float *value) {
    si->inputs[index] = value;
}

int checkLogic(SlangInterpreter* si, int* i) {
    float left = l3_expression(si, i);

    int operand = 0;

    if (getToken(si, *i).tt == ASSIGN) {
        operand = 1;
        consume(i, si->tokens[*i], ASSIGN);
    }
    else if (getToken(si, *i).tt == SMALLER) {
        operand = 2;
        consume(i, si->tokens[*i], SMALLER);
    }
    else if (getToken(si, *i).tt == GREATER) {
        operand = 3;
        consume(i, si->tokens[*i], GREATER);
    }
    else {
        LOGERROR("MALFORMED LOGIC STATEMENT.");
        exit(-1);
    }

    float right = l3_expression(si, i);

    switch (operand) {
        case 1:
            if (left == right) {
                return 1;
            }
            else {
                return 0;
            }
            break;
        case 2:
            if (left < right) {
                return 1;
            }
            else {
                return 0;
            }
            break;
        case 3:
            if (left > right) {
                return 1;
            }
            else {
                return 0;
            }
            break;
    }
}


#ifdef __cplusplus
}
#endif
