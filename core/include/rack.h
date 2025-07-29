#ifndef SLANG_RACK_H
#define SLANG_RACK_H
#include "../../modules/oscillators/include/oscillator.h"
#include "../../modules/data/include/binaryData.h"
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"


typedef struct Rack {
    int* sampleRate;
    int* bufferSize;
    Oscillator** oscillators;
    int numOscillators;
} Rack;

void *getOscillator(Rack* rack, char* name);

void setSampleRateForAllOscillators(Rack* rack, int sampleRate);

void addOscillator(Rack* rack, Oscillator* input);

float getSample(Rack* rack);

#endif
