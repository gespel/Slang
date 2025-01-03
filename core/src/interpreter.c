#include "../include/interpreter.h"

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
    int numTokens = si->numTokens;
    Token* tokens = si->tokens;

    for(int i = 0; i < numTokens; i++) {
        if(tokens[i].tt == IDENTIFIER) {
            char* name = tokens[i].value;
            consume(&i, tokens[i], IDENTIFIER);
            if(tokens[i].tt == ASSIGN) {
                consume(&i, tokens[i], ASSIGN);
                //peek(tokens[i], NUMBER);
                double var_value = l1_expression(si, &i);

                Variable* temp_var = malloc(sizeof(Variable));
                temp_var->name = name;
                temp_var->value = var_value;

                addVariable(si, temp_var);
            }
            else if(tokens[i].tt == PARANTHESISLEFT) {
                consume(&i, tokens[i], PARANTHESISLEFT);
                consume(&i, tokens[i], PARANTHESISRIGHT);
                peek(tokens[i], SEMICOLON);

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
            inc(&i);  
            consume(&i, tokens[i], SEMICOLON);
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

            addFunction(si, temp);
        }
        else if(getToken(si, i).tt == SEMICOLON) {
            consume(&i, tokens[i], SEMICOLON);
            printDebugMessage("Empty line.");
        }
        else {
            printf("[ERROR] Wrong token exception! Type: %s Value: %s\n", tokenTypeToString(si->tokens[i].tt), si->tokens[i].value);
        }
        i--;
    }
    return 1;
}

double terminal(SlangInterpreter* s, int* i) {
    if(s->tokens[*i].tt == NUMBER) {
        double out = atof(s->tokens[*i].value);
        (*i)++;
        return out;
    }
    else if(s->tokens[*i].tt == IDENTIFIER) {
        double out = getVariableByName(s, s->tokens[*i].value)->value;
        (*i)++;
        return out;
    }
    return 0;
}

double l1_expression(SlangInterpreter* s, int* i) {
    printDebugMessage("Called expression");
    //printDebugMessage(tokenTypeToString(s->tokens[*i].tt));
    //printDebugMessage(s->tokens[*i].value);
    double left, right;
    if(s->tokens[*i].tt == PARANTHESISLEFT) {
        //printDebugMessage("Hit parantheses!");
        consume(i, s->tokens[*i], PARANTHESISLEFT);
        left = l1_expression(s, i);
        consume(i, s->tokens[*i], PARANTHESISRIGHT); 
    }
    else {
        //printDebugMessage("No parantheses. Regular left...");
        left = terminal(s, i);
    }
   	
    switch(s->tokens[*i].tt) {
        case PLUS:
            printDebugMessage("Doing addition now!");
            consume(i, s->tokens[*i], PLUS);
            right = l1_expression(s, i);
            printf("\t%f + %f\n", left, right);
            return left + right;
            break;
        case MINUS:
            printDebugMessage("Doing subtraction now!");
            consume(i, s->tokens[*i], MINUS);
            right = l1_expression(s, i);
            return left - right;
            break;
        case MULTIPLY:
            printDebugMessage("Doing multiplication now!");
            consume(i, s->tokens[*i], MULTIPLY); 
            right = l1_expression(s, i);
            printf("\t%f * %f\n", left, right);
            return left * right;
            break;
        case DIVIDE:
            printDebugMessage("Doing division now!");
            consume(i, s->tokens[*i], DIVIDE); 
            right = l1_expression(s, i);
            return left / right;
            break;
        case SEMICOLON:
            printDebugMessage("End of expression!");
            (*i)--;
            //(*i)++;
            return left;
        case PARANTHESISRIGHT:
            printDebugMessage("Hit parantheses right!");
            printf("\treturning %f\n", left);
            return left;
        default:
            printf("[ERROR] Unexpected token! %s, %s\n", tokenTypeToString(s->tokens[*i].tt), s->tokens[*i].value);
            exit(EXIT_FAILURE);
            break;
    }
    //(*i)++;
    return 0;
}






















