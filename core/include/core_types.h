//
// Created by Sten on 09.08.2025.
//

#ifndef CORE_TYPES_H
#define CORE_TYPES_H
#include "../../modules/modules.h"
#include "modules/envelope/include/envelope_types.h"

typedef struct SlangInterpreter SlangInterpreter;

typedef enum SlangLogLevel {
    DBG,
    INFO,
    WARN,
    ERR,
} SlangLogLevel;

typedef enum TokenType {
    IDENTIFIER_TOKEN_T,
    NUMBER_TOKEN_T,
    FUNCTION_TOKEN_T,
    SEMICOLON_TOKEN_T,
    BRACKETLEFT_TOKEN_T,
    BRACKETRIGHT_TOKEN_T,
    PARANTHESISLEFT_TOKEN_T,
    PARANTHESISRIGHT_TOKEN_T,
    SQUAREBRACKETLEFT_TOKEN_T,
    SQUAREBRACKETRIGHT_TOKEN_T,
    ASSIGN_TOKEN_T,
    PLUS_TOKEN_T,
    MINUS_TOKEN_T,
    MULTIPLY_TOKEN_T,
    DIVIDE_TOKEN_T,
    RETURN_TOKEN_T,
    FOR_TOKEN_T,
    IF_TOKEN_T,
    COMMA_TOKEN_T,
    WHILE_TOKEN_T,
    SMALLER_TOKEN_T,
    GREATER_TOKEN_T,
    SINEOSC_TOKEN_T,
    TRUESINEOSC_TOKEN_T,
    SAWOSC_TOKEN_T,
    WAVEOSC_TOKEN_T,
    SQUAREOSC_TOKEN_T,
    TRIANGLEOSC_TOKEN_T,
    RANDOMOSC_TOKEN_T,
    TERRAINOSC_TOKEN_T,
    RANDOM_TOKEN_T,
    RANDOMINT_TOKEN_T,
    LOWPASSFILTERTOKEN_TOKEN_T,
    HIGHPASSFILTERTOKEN_TOKEN_T,
    LINENVELOPEGENERATORTOKEN_TOKEN_T,
    STEPSEQ_TOKEN_T,
    INPUTA_TOKEN_T,
    INPUTB_TOKEN_T,
    INPUTC_TOKEN_T,
    INPUTD_TOKEN_T,
    MAIN_TOKEN_T,
    NOTEMARKER_TOKEN_T,
} TokenType;

typedef struct Token {
    TokenType tt;
    char* value;
} Token;

typedef struct Variable {
    char* name;
    float value;
} Variable;

typedef struct Function {
    char* name;
    Token* function_tokens;
    size_t function_tokens_length;
    char** vars;
    size_t vars_length;
} Function;

typedef struct Rack {
    int* sampleRate;
    int* bufferSize;
    Oscillator** oscillators;
    int numOscillators;
    StepSequencer** stepSequencers;
    int numStepSequencers;
    SampleSource **sampleSources;
    int numSampleSources;
    EnvelopeGenerator **envelopeGenerators;
    int numEnvelopeGenerators;
    Filter **filters;
    int numFilters;
    SlangInterpreter* interpreter;
} Rack;

typedef struct SlangInterpreter {
    int functions_length;
    Function* functions[8192];
    int vars_length;
    Variable* variables[8192];
    Token* tokens;
    int numTokens;
    int openBrackets;
    int last_token_index;
    Rack* main_rack;
    float *inputs[4];
    int sampleRate;
    int bufferSize;
    int interpretedCount;
} SlangInterpreter;

typedef struct SlangBufferCore {
    SlangInterpreter* interpreter;
    float* buffer;
    int bufferSize;
    int sampleRate;
} SlangBufferCore;

#endif //CORE_TYPES_H
