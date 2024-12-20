//
// Created by stenh
//
#include "slang-lib.h"

int main() {
    char a[] = "fn sten() { a = b; } \n x = 3;";

    int length = 0;
    Token* out = tokenize(a, &length);

    printf("%d tokens!\n", length);
    interpret(out, length);
    printAllFunctions();
    printAllVariables();
    free(out);

    return 0;
}
