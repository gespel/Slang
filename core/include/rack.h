#ifndef SLANG_RACK_H
#define SLANG_RACK_H
#include "../../modules/include/oscillator.h"
#include <stdlib.h>

typedef struct Rack {
    SineOscillator** sine_oscillators;
    int numSineOscillators;
    int sampleRate;
    int bufferSize;
} Rack;

void addSineOscillator(Rack* rack, SineOscillator* input);

#endif
