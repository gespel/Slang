#include "core/include/interpreter.h"
#include "core/include/core_types.h"
#include "core/include/rack.h"
#include "core/include/tools.h"
#include "include/parser.h"
#include "modules/sample-source/include/sample_source.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif


void increase(int* i) {
    (*i)++;
}

void copyInterpreter(SlangInterpreter* src, SlangInterpreter* dst) {
    memcpy(dst, src, sizeof(SlangInterpreter));
    dst->tokens = malloc(sizeof(Token) * src->numTokens);
    memcpy(dst->tokens, src->tokens, sizeof(Token) * src->numTokens);

    for (int i = 0; i < src->functions_length; i++) {
        dst->functions[i] = malloc(sizeof(Function));
        memcpy(dst->functions[i], src->functions[i], sizeof(Function));
    }

    for (int i = 0; i < src->vars_length; i++) {
        dst->variables[i] = malloc(sizeof(Variable));
        memcpy(dst->variables[i], src->variables[i], sizeof(Variable));
    }
    dst->functions_length = src->functions_length;
    dst->vars_length = src->vars_length;
    dst->numTokens = src->numTokens;
    dst->openBrackets = src->openBrackets;
    dst->last_token_index = src->last_token_index;
    dst->main_rack = src->main_rack;
}

int consume(int* i, Token token, TokenType expected) {
    //LOGDEBUG("Consuming %s now. (Expecting %s): %s", tokenTypeToString(token.tt), tokenTypeToString(expected), token.value);
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
    for(size_t i = 0; i < si->vars_length; i++) {

    }
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
    out->main_rack = createRack(&out->sampleRate, &out->bufferSize);
    out->main_rack->interpreter = out;
    out->functions_length = 0;
    out->vars_length = 0;
    out->interpretedCount = 0;
    return out;
}

void destroySlangInterpreter(SlangInterpreter* si) {
    for(int i = 0; i < si->functions_length; i++) {
        free(si->functions[i]);
    }
    for(int i = 0; i < si->vars_length; i++) {
        free(si->variables[i]);
    }
    for(int i = 0; i < si->numTokens; i++) {
        free(si->tokens[i].value);
    }
    for(int i = 0; i < si->main_rack->numOscillators; i++) {
        free(si->main_rack->oscillators[i]);
    }
    free(si->main_rack);
    free(si);
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
/*#ifdef SLANG_DEBUG
    LOGDEBUG("Function %s was not found!", name);
#endif*/
    return NULL;
}

float interpret(SlangInterpreter* si) {
    printDebugMessage(INFO, "Interpreter started!");
    si->interpretedCount += 1;
    //printAllVariables(si);
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
            float out1 = l3_expression(si, &i);
            LOGDEBUG("Returning now! Value: %lf", out1);
            return out1;
        }
        else if(getToken(si, i).tt == SEMICOLON) {
            consume(&i, tokens[i], SEMICOLON);
            printDebugMessage(DBG, "Empty line.");
        } 
        else if(getToken(si, i).tt == IF) {
            parseIf(si, &i);
        }
        else if(getToken(si, i).tt == BRACKETRIGHT) {
            if((si->openBrackets) > 0) {
                (si->openBrackets)--;
                consume(&i, tokens[i], BRACKETRIGHT);
            }
            else {
                LOGERROR("[ERROR] CLOSING BRACKET IS UNEXPECTED! Current openBrackets = %d", si->openBrackets);
                exit(-1);
            }
        }
        else if (getToken(si, i).tt == LOWPASSFILTERTOKEN || getToken(si, i).tt == HIGHPASSFILTERTOKEN) {
            parseFilter(si, &i);
        }
        else if (getToken(si, i).tt == LINENVELOPEGENERATORTOKEN) {
            parseEnvelopeGenerator(si, &i, NULL);
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
            break;
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
                    LOGDEBUG("argument: %lf", arguments[arg_counter]);
                    arg_counter++;
                    if(si->tokens[*i].tt != PARANTHESISRIGHT) {
                        consume(i, si->tokens[*i], COMMA);
                    }
                }
                
                if(arg_counter != f->vars_length) {
                    LOGERROR("Number of function call is not equal to function definition!");
                    exit(-1);
                }
                
                consume(i, si->tokens[*i], PARANTHESISRIGHT);

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
                //function_interpreter->main_rack = si->main_rack;
                //si->sampleRate = function_interpreter->sampleRate;
                //si->bufferSize = function_interpreter->bufferSize;
                out = interpret(function_interpreter);
                       
                free(function_interpreter);
            }
            else if(getSampleSource(si->main_rack, si->tokens[*i].value)) {
                SampleSource* ss = getSampleSource(si->main_rack, si->tokens[*i].value);
                out = getSampleSourceSample(ss);
                consume(i, si->tokens[*i], IDENTIFIER);
                //LOGDEBUG("Retrieved sample from oscillator: %f", out);
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
            break;
        case NOTEMARKER:
            consume(i, si->tokens[*i], NOTEMARKER);
            out = noteNameToFrequency(si->tokens[*i].value);
            consume(i, si->tokens[*i], IDENTIFIER);
            break;
        case INPUTA:
            out = si->inputs[0][0];
            break;
        case INPUTB:
            out = si->inputs[1][0];
            break;
        case INPUTC:
            out = si->inputs[2][0];
            break;
        case INPUTD:
            out = si->inputs[3][0];
            break;
        case RANDOM:
            consume(i, si->tokens[*i], RANDOM);
            consume(i, si->tokens[*i], PARANTHESISLEFT);
            float lowerFloatBound = atof(si->tokens[*i].value);
            consume(i, si->tokens[*i], NUMBER);
            consume(i, si->tokens[*i], COMMA);
            float upperFloatBound = atof(si->tokens[*i].value);
            consume(i, si->tokens[*i], NUMBER);
            consume(i, si->tokens[*i], PARANTHESISRIGHT);
            float rFloat = randomFloat(lowerFloatBound, upperFloatBound);
            out = rFloat;
            break;
        case RANDOMINT:
            consume(i, si->tokens[*i], RANDOMINT);
            consume(i, si->tokens[*i], PARANTHESISLEFT);
            int lowerIntBound = atoi(si->tokens[*i].value);
            consume(i, si->tokens[*i], NUMBER);
            consume(i, si->tokens[*i], COMMA);
            int upperIntBound = atoi(si->tokens[*i].value);
            consume(i, si->tokens[*i], NUMBER);
            consume(i, si->tokens[*i], PARANTHESISRIGHT);
            int rInt = randomInt(lowerIntBound, upperIntBound);
            out = (float)rInt;
            break;
        default:
            LOGERROR("Terminal expected NUMBER or IDENTIFIER got %s", tokenTypeToString(si->tokens[*i].tt));
            exit(-1);
    }
    //LOGDEBUG("Terminal: %lf", out);
    return out;
}

float l3_expression(SlangInterpreter* si, int* i) {
    float left = l2_expression(si, i);
    while (1) {
        switch(getToken(si, *i).tt) {
            case PLUS:
                consume(i, si->tokens[*i], PLUS);
                left += l2_expression(si, i);  // <-- korrekt!
                break;
            case MINUS:
                consume(i, si->tokens[*i], MINUS);
                left -= l2_expression(si, i);  // <-- korrekt!
                break;
            default:
                //LOGDEBUG("l3 Returning left: %lf", left);
                return left;
        }
    }
}

float l2_expression(SlangInterpreter* si, int* i) {
    float left = l1_expression(si, i);
    while (1) {
        switch(getToken(si, *i).tt) {
            case MULTIPLY:
                consume(i, si->tokens[*i], MULTIPLY);
                left *= l1_expression(si, i);  // <-- korrekt!
                break;
            case DIVIDE:
                consume(i, si->tokens[*i], DIVIDE);
                left /= l1_expression(si, i);  // <-- korrekt!
                break;
            default:
                //LOGDEBUG("l2 Returning left: %lf", left);
                return left;
        }
    }
}

float l1_expression(SlangInterpreter* si, int* i) {
    //printDebugMessage(DBG, "Called expression");
    //printDebugMessage(DBG, tokenTypeToString(si->tokens[*i].tt));
    //printDebugMessage(DBG, si->tokens[*i].value);
    float left;
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
    //LOGDEBUG("l1 Returning left: %lf", left);
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
    if (token.tt == SEMICOLON || token.tt == SAWOSC || token.tt == TRUESINEOSC || token.tt == WAVEOSC || token.tt == SINEOSC || token.tt == SQUAREOSC || token.tt == TRIANGLEOSC || token.tt == TERRAINOSC) {
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
    return 0;
}

#ifdef __cplusplus
}
#endif
