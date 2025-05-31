#include "../include/function.h"

Function* createFunction(char* name, Token* function_tokens, size_t function_tokens_length, char** vars) {
    Function* out = malloc(sizeof(Function));
    out->name = name;
    out->function_tokens = function_tokens;
    out->function_tokens_length = function_tokens_length;
    out->vars;
    return out;
}
