#ifndef SLANG_VARIABLE_H
#define SLANG_VARIABLE_H
#include "tokenizer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Variable {
    char* name;
    float value;
} Variable;

#ifdef __cplusplus
}
#endif

#endif

