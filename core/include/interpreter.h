//
// Created by sten on 12.06.24.
//
#pragma once
struct Rack;
typedef struct Rack Rack;
#define SLANG_DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tokenizer.h"
#include "tools.h"
#include "function.h"
#include "variable.h"
#include "rack.h"
#include "parser.h"

typedef struct SlangInterpreter {
    int functions_length;
    Function* functions[8192];
    int vars_length;
    Variable* variables[8192];
    Token* tokens;
    int numTokens;
    int openBrackets;
    int last_token_index;
    Rack* main_rack;
    float *inputs[4];
} SlangInterpreter;

SlangInterpreter* createSlangInterpreter(Token* tokens, size_t numTokens);

int getInputIndex(Token token);

void linkInput(SlangInterpreter* si, int nr, float *value);

void addTokensToInterpreter(SlangInterpreter* si, Token* tokens, size_t numTokens);

float interpret(SlangInterpreter* si);

float terminal(SlangInterpreter* si, int* i);

float l1_expression(SlangInterpreter* si, int* i);

float l2_expression(SlangInterpreter* si, int* i);

float l3_expression(SlangInterpreter* si, int* i);

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

void printAllOscillators(SlangInterpreter* si);

char* getInterpreterStatusString(SlangInterpreter* si);

int isOscillator(Token token);


