//
// Created by Sten on 28.06.2025.
//
#pragma once
#include "core/include/core_types.h"
#include "interpreter.h"

void parseOscillators(SlangInterpreter* si, int* i, char *name);

void parseFilter(SlangInterpreter* si, int* i);

void parseStepSequencer(SlangInterpreter* si, int* i, char* name);

void parseFunction(SlangInterpreter* si, int* i);

void parseExpression(SlangInterpreter* si, int* i);

void parseIf(SlangInterpreter* si, int* i);

void parseEnvelopeGenerator(SlangInterpreter* si, int* i, char* name);

void parseOscillatorSuffixArguments(SlangInterpreter* si, int* i, float* freqptr, int* is_output, int *is_cv);