//
// Created by Sten on 09.08.2025.
//

#ifndef CORE_TYPES_H
#define CORE_TYPES_H
#include "modules/modules.h"
#include "modules/envelope/include/envelope_types.h"
#include "modules/reverb/include/reverb_types.h"

typedef struct SlangInterpreter SlangInterpreter;

typedef enum SlangLogLevel {
    DBG,
    INFO,
    WARN,
    ERR,
} SlangLogLevel;

typedef enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_FUNCTION,
    TOKEN_SEMICOLON,
    TOKEN_BRACKETLEFT,
    TOKEN_BRACKETRIGHT,
    TOKEN_PARANTHESISLEFT,
    TOKEN_PARANTHESISRIGHT,
    TOKEN_SQUAREBRACKETLEFT,
    TOKEN_SQUAREBRACKETRIGHT,
    TOKEN_ASSIGN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_RETURN,
    TOKEN_FOR,
    TOKEN_IF,
    TOKEN_COMMA,
    TOKEN_WHILE,
    TOKEN_SMALLER,
    TOKEN_GREATER,
    TOKEN_SINEOSC,
    TOKEN_TRUESINEOSC,
    TOKEN_SAWOSC,
    TOKEN_WAVEOSC,
    TOKEN_SQUAREOSC,
    TOKEN_TRIANGLEOSC,
    TOKEN_RANDOMOSC,
    TOKEN_TERRAINOSC,
    TOKEN_RANDOM,
    TOKEN_RANDOMINT,
    TOKEN_LOWPASSFILTER,
    TOKEN_HIGHPASSFILTER,
    TOKEN_LINENVELOPE,
    TOKEN_STEPSEQ,
    TOKEN_INPUTA,
    TOKEN_INPUTB,
    TOKEN_INPUTC,
    TOKEN_INPUTD,
    TOKEN_MAIN,
    TOKEN_NOTEMARKER,
    TOKEN_SPRINGREVERB,
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
    Reverb **reverbs;
    int numReverb;
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
