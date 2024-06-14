//
// Created by stenh
//
#include "slang-lib.h"

int main() {
    char a[] = "x = 3;";
    int length = 0;
    Token* out = tokenize(a, &length);
    printf("%d tokens!\n", length);
    interpret(out, length);
    printTokens(out, length);
    free(out);

    return 0;
}
