#ifndef SLANG_FUNCTION_H
#define SLANG_FUNCTION_H
#include "tokenizer.h"

typedef struct Function {
    char* name;
    Token* function_tokens;
    int function_tokens_length;
} Function;

#endif

