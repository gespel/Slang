#include "core/include/function.h"

Function* createFunction(char* name, Token* function_tokens, size_t function_tokens_length, char** vars, size_t vars_length) {
    Function* out = malloc(sizeof(Function));
    out->name = name;
    out->function_tokens = function_tokens;
    out->function_tokens_length = function_tokens_length;
    out->vars = vars;
    out->vars_length = vars_length;
    return out;
}
