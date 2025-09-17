//
// Created by Sten on 28.06.2025.
//
#pragma once
#include "interpreter.h"


void parseOscillators(SlangInterpreter* si, int* i, char *name);

void parseFunction(SlangInterpreter* si, int* i);

void parseExpression(SlangInterpreter* si, int* i);

void parseOscillatorSuffixArguments(SlangInterpreter* si, int* i, float** freqptr, float* frequency_multiplier, int* is_output);

