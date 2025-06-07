#ifndef SLANG_RACK_H
#define SLANG_RACK_H
#include "oscillator.h"

typedef struct Rack {
    SineOscillator** sine_oscs;
    size_t num_sine_oscs;
} Rack;

#endif
