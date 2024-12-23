//
// Created by stenh
//
#include "slang-lib.h"

int main() {
    char a[] = "fn sten() { a = 2; asd = 123; } \n x = 3; y = 5;";

    int length = 0;
    Token* out = tokenize(a, &length);

    printf("%d tokens!\n", length);
    interpret(out, length);
    printAllFunctions();
    printAllVariables();
    free(out);

    return 0;
}
