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

SlangInterpreter* createSlangInterpreter(Token* tokens, size_t numTokens);

double interpret(SlangInterpreter* s);

double terminal(SlangInterpreter* s, int* i);

double l1_expression(SlangInterpreter* s, int* i);

double l2_expression(SlangInterpreter* s, int* i);

void increase(int* i);

int consume(int* i, Token token, TokenType expected);

int peek(Token token, TokenType expected);

void addFunction(SlangInterpreter* si, Function* input);

Function* getFunctionByName(SlangInterpreter* si, char* name);

void printAllFunctions(SlangInterpreter* si);

void addVariable(SlangInterpreter* si, Variable* input);

Variable* getVariableByName(SlangInterpreter* si, char* name);

void inc(int* i);

void dec(int* i);

void printAllVariables(SlangInterpreter* si);

#endif //SLANG_INTERPRETER_H
