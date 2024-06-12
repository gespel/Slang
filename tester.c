//
// Created by stenh on 11.06.2024.
//
#include "slang-lib.h"

int main() {
    char a[] = "Sten ist fn 3341 a1";
    int length = 0;
    Token* out = tokenize(a, &length);
    printf("%d tokens!\n", length);

    for(int j = 0; j < length; j++) {
        printf("%s %s\n", out[j].value, tokenTypeToString(out[j].tt));
    }
    free(out);

    return 0;
}
