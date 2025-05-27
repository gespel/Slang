//
// Created by sten on 12.06.24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tokenizer.h"
#include "tools.h"
#include "function.h"
#include "variable.h"
#ifndef SLANG_INTERPRETER_H
#define SLANG_INTERPRETER_H
#define DEBUG

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SlangInterpreter {
    size_t functions_length;
    Function* functions[8192];
    size_t vars_length;
    Variable* variables[8192];
    Token* tokens;
    size_t numTokens;
    size_t openBrackets;
    int last_token_index;
} SlangInterpreter;

SlangInterpreter* createSlangInterpreter(Token* tokens, size_t numTokens);

void addTokensToInterpreter(SlangInterpreter* si, Token* tokens, size_t numTokens);

double interpret(SlangInterpreter* s);

double terminal(SlangInterpreter* si, int* i);

double l1_expression(SlangInterpreter* si, int* i);

double l2_expression(SlangInterpreter* si, int* i);

double l3_expression(SlangInterpreter* si, int* i);

void increase(int* i);

int consume(int* i, Token token, TokenType expected);

int peek(Token token, TokenType expected);

void addFunction(SlangInterpreter* si, Function* input);

Function* getFunctionByName(SlangInterpreter* si, char* name);

void printAllFunctions(SlangInterpreter* si);

void addVariable(SlangInterpreter* si, Variable* input);

void removeVariable(SlangInterpreter* si, char* name);

Variable* getVariableByName(SlangInterpreter* si, char* name);

void inc(int* i);

void dec(int* i);

void printAllVariables(SlangInterpreter* si);

#ifdef __cplusplus
}
#endif

#endif //SLANG_INTERPRETER_H
