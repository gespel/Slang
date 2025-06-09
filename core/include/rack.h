#ifndef SLANG_RACK_H
#define SLANG_RACK_H
#include "../../modules/include/oscillator.h"

typedef struct Rack {
    SineOscillator** sine_oscillators;
    int num_sine_oscillators;
} Rack;

void addSineOscillator(Rack* rack, SineOscillator* input);

#endif
