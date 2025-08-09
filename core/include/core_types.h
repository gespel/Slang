//
// Created by Sten on 09.08.2025.
//

#ifndef CORE_TYPES_H
#define CORE_TYPES_H

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

#endif //CORE_TYPES_H
