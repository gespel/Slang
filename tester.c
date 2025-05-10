//
// Created by stenh
//
#include "slang-lib.h"
//#define LIBRARY
#ifndef LIBRARY

int main() {
    char a[] = "x = 3; y = 2; z = (x + y) * 2; fn test() {yx = 6; return yx;} re = test(3, 2); asd = 15; if(test() == 5) {it = 15;}";

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
