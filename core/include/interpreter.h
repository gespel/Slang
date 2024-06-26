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

int interpret(Token* tokens, int numTokens);

int functions_length = 0;
Function functions[8192];

int vars_length = 0;
Variable variables[8192];

void addFunction(Function input) {
    functions[functions_length] = input;
    functions_length++;
}

void printAllFunctions() {
    for(int i = 0; i < functions_length; i++) {
        printf("%s:\n", functions[i].name);
        for(int j = 0; j < functions[i].function_tokens_length; j++) {
            printf("\t%s\n", functions[i].function_tokens[j].value);
        }
    }
}

void addVariable(Variable input) {
    variables[vars_length] = input;
    vars_length++;
}

void printAllVariables() {
    for(int i = 0; i < vars_length; i++) {
        printf("%s: %lf\n", variables[i].name, variables[i].value);
    }
}

#endif //SLANG_INTERPRETER_H
