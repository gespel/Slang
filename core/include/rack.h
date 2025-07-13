#ifndef SLANG_RACK_H
#define SLANG_RACK_H
#include "../../modules/include/oscillator.h"
#include "../../modules/include/wavetable.h"
#include "../../modules/include/binaryData.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Rack {
    SineOscillator** sine_oscillators;
    int numSineOscillators;
    WavetableOscillator** wave_oscillators;
    int numWaveOscillators;
    SawtoothOscillator** sawtooth_oscillators;
    int numSawtoothOscillators;
    int* sampleRate;
    int* bufferSize;
} Rack;

void addSineOscillator(Rack* rack, SineOscillator* input);

SineOscillator* getSineOscillator(Rack* rack, char* name);

void *getOscillator(Rack* rack, char* name);

void addWavetableOscillator(Rack* rack, WavetableOscillator* input);

void addSawtoothOscillator(Rack* rack, SawtoothOscillator* input);

void setSampleRateForAllOscillators(Rack* rack, int sampleRate);

#endif
