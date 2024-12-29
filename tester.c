//
// Created by stenh
//
#include "slang-lib.h"

int main() {
    char a[] = "fn sten() { a = 2; asd = 123; } \n x = 3; sten(); y = 15; z = x; xx = 1 + 2; xy = x + y; xz = x + 1;";

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
