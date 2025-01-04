#ifndef SLANG_FUNCTION_H
#define SLANG_FUNCTION_H
#include "tokenizer.h"

typedef struct Function {
    char* name;
    Token* function_tokens;
    size_t function_tokens_length;
} Function;

Function* createFunction(char* name, Token* function_tokens, size_t function_tokens_length) {
    Function* out = malloc(sizeof(Function));
    out->name = name;
    out->function_tokens = function_tokens;
    out->function_tokens_length = function_tokens_length;
    return out;
}

#endif

