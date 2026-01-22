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
    IDENTIFIER,
    NUMBER,
    FUNCTION,
    SEMICOLON,
    BRACKETLEFT,
    BRACKETRIGHT,
    PARANTHESISLEFT,
    PARANTHESISRIGHT,
    SQUAREBRACKETLEFT,
    SQUAREBRACKETRIGHT,
    ASSIGN,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    RETURN,
    FOR,
    IF,
    COMMA,
    WHILE,
    SMALLER,
    GREATER,
    SINEOSC,
    TRUESINEOSC,
    SAWOSC,
    WAVEOSC,
    SQUAREOSC,
    TRIANGLEOSC,
    TERRAINOSC,
    RANDOM,
    RANDOMINT,
    LOWPASSFILTERTOKEN,
    HIGHPASSFILTERTOKEN,
    LINENVELOPEGENERATORTOKEN,
    STEPSEQ,
    INPUTA,
    INPUTB,
    INPUTC,
    INPUTD,
    NOTEMARKER,
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
