//
// Created by stenh
//
#include "slang-lib.h"
//#define LIBRARY
#ifndef LIBRARY

int main() {
    char a[] = "x = 3; y = 2; xy = ((x + y)) * (3 + 1); xx = x * (x + x); fn fun() { sten = 3; } fun(); fun();";

    int length = 0;
    Token* tokens = tokenize(a, &length);
    //printTokens(tokens, length);

    printf("%d tokens!\n", length);
    SlangInterpreter* main_interpreter = createSlangInterpreter(tokens, length);
    interpret(main_interpreter);
    printAllFunctions(main_interpreter);
    printAllVariables(main_interpreter);
    free(main_interpreter);

    return 0;
}
#endif
