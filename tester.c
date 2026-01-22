//
// Created by stenh
//
#include "slang-lib.h"
//#define LIBRARY
#ifndef LIBRARY


void testInterpreter() {
    char a[] = "x = 3; y = 2; z = (x + y) * 2; fn test() {yx = 6; return yx;} re = test(3, 2); asd = 15; if(test() == 5) {it = 15;}";
    //char a[] = "x = 3;";

    int length = 0;
    Token* tokens = tokenize(a, &length);
    //printTokens(tokens, length);


    printf("%d tokens!\n", length);
    SlangInterpreter* main_interpreter = createSlangInterpreter(tokens, length);
    interpret(main_interpreter);
    printAllFunctions(main_interpreter);
    printAllVariables(main_interpreter);
    free(main_interpreter); 
}

void testEnvelopeGenerator() {
    LinearEnvelopeGenerator* lin = createLinearEnvelopeGenerator("test", 48000, 0.1, 0.1, 1, 0.2);
    triggerLinearEnvelopeGenerator(lin);
    for(int i = 0; i < 74000; i++) {
        //printf("%f\n", getLinearEnvelopeGeneratorSample(lin));
        tickLinearEnvelopeGenerator(lin);
    }
}

int main() {
    testEnvelopeGenerator();
    
    return 0;
}
#endif
