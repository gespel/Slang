#ifndef SLANG_RACK_H
#define SLANG_RACK_H
#include "oscillator.h"

typedef struct Rack {
    SineOscillator** sine_oscs;
    int num_sine_oscs;
} Rack;

void addSineOscillator(Rack* rack, SineOscillator* input);

#endif
