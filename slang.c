//
// Created by stenh
//
#include "slang-lib.h"
//#define LIBRARY
#ifndef LIBRARY

int main(int argc, char **argv) {
    if(argc == 2) {
        char p[16384];
        char buff[2048];
        FILE *f = fopen(argv[1], "r");

        while(fgets(buff, 2048, f)) {
            strcat(p, buff);
        }
        printf("Read programm: %s\n", p);

        int length = 0;
        Token* tokens = tokenize(p, &length);
        //printTokens(tokens, length);


        printf("%d tokens!\n", length);
        SlangInterpreter* main_interpreter = createSlangInterpreter(tokens, length);
        interpret(main_interpreter);
        printAllFunctions(main_interpreter);
        printAllVariables(main_interpreter);
        free(main_interpreter); 
    }
    else {
        printf("Wrong number of arguments!\nUsage: slang <file>\n");
    }
    
    
    return 0;
}
#endif
