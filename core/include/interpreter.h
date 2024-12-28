//
// Created by sten on 12.06.24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "tools.h"
#include "function.h"
#include "variable.h"
#ifndef SLANG_INTERPRETER_H
#define SLANG_INTERPRETER_H
#define DEBUG

typedef struct SlangInterpreter {
    size_t functions_length;
    Function* functions[8192];
    size_t vars_length;
    Variable* variables[8192];
    Token* tokens;
    size_t numTokens;
} SlangInterpreter;


int interpret(SlangInterpreter* s);

double terminal(SlangInterpreter* s, int* i);

double l1_expression(SlangInterpreter* s, int* i);
//int interpret(Token* tokens, int numTokens);

//int functions_length = 0;
//Function* functions[8192];

//int vars_length = 0;
//Variable* variables[8192];



int consume(int* i, Token token, TokenType expected) {
#ifdef DEBUG
    printf("[DEBUG] Consuming %s now. (Expecting %s): %s\n", tokenTypeToString(token.tt), tokenTypeToString(expected), token.value);
#endif
    if(token.tt == expected) {
        (*i)++;
        return 1;
    }
    else {
        printf("\nERROR! WRONG TOKEN! EXPECTED \"%s\" GOT \"%s\" INSTEAD\n", tokenTypeToString(expected), tokenTypeToString(token.tt));
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

Function* getFunctionByName(SlangInterpreter* si, char* name);

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

#endif //SLANG_INTERPRETER_H
