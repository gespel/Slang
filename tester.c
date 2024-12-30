//
// Created by stenh
//
#include "slang-lib.h"

int main() {
    char a[] = "x = 1; y = 2; z = 14; a = 3; b = 4; xy = x + y; exp = x + y + b + xy * 2; fn sten() { lina = 3; } sten(); p = (1 + 3) * 2 / 5;";

    int length = 0;
    Token* tokens = tokenize(a, &length);

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
