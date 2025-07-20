#ifndef SLANG_RACK_H
#define SLANG_RACK_H
#include "../../modules/oscillators/include/oscillator.h"
#include "../../modules/data/include/binaryData.h"
#include <stdlib.h>
#include <stdio.h>

typedef union Oscillators {
    SineOscillator *sine;
    SawtoothOscillator *sawtooth;
    WavetableOscillator *wavetable;
    SquareOscillator *square;
} Oscillators;

typedef struct Rack {
    SineOscillator** sine_oscillators;
    int numSineOscillators;
    WavetableOscillator** wave_oscillators;
    int numWaveOscillators;
    SawtoothOscillator** sawtooth_oscillators;
    int numSawtoothOscillators;
    int* sampleRate;
    int* bufferSize;
    Oscillators *oscillators;
    int numOscillators;
} Rack;

void addSineOscillator(Rack* rack, SineOscillator* input);

SineOscillator* getSineOscillator(Rack* rack, char* name);

void *getOscillator(Rack* rack, char* name);

void addWavetableOscillator(Rack* rack, WavetableOscillator* input);

void addSawtoothOscillator(Rack* rack, SawtoothOscillator* input);

void setSampleRateForAllOscillators(Rack* rack, int sampleRate);

void addOscillator(Rack *rack, Oscillators *oscillator);

#endif
