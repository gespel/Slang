//
// Created by stenh
//
#include "slang-lib.h"

int main() {
    char a[] = "x = 3; y = 2; xy = ((x + y)) * (3 + 1); xx = x * (x + x); fn fun() { sten = 3; } fun(); fun();";

    int length = 0;
    Token* tokens = tokenize(a, &length);
    //printTokens(tokens, length);

    printf("%d tokens!\n", length);
    SlangInterpreter* main_interpreter = malloc(sizeof(SlangInterpreter));
    main_interpreter->tokens = tokens;
    main_interpreter->numTokens = length;
    interpret(main_interpreter);
    printAllFunctions(main_interpreter);
    printAllVariables(main_interpreter);
    free(main_interpreter);

    return 0;
}
