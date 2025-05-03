#ifndef SLANG_FUNCTION_H
#define SLANG_FUNCTION_H
#include "tokenizer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Function {
    char* name;
    Token* function_tokens;
    size_t function_tokens_length;
} Function;

Function* createFunction(char* name, Token* function_tokens, size_t function_tokens_length);

#ifdef __cplusplus
}
#endif

#endif

