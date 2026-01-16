//
// Created by sten on 16.07.25.
//
#include "oscillators/include/sawtooth.h"
#include <stdlib.h>

float getSawtoothSample(SawtoothOscillator* oscillator) {
    return oscillator->sample * oscillator->volume;
}

void tickSawtoothOscillator(SawtoothOscillator *oscillator) {
    if (oscillator->isCV == 1) {
        if (oscillator->sample > 2) {
            oscillator->sample = 0;
        }
    }
    else {
        if (oscillator->sample > 1) {
            oscillator->sample = -1.0;
        }
    }
    float freq = oscillator->frequency;
    oscillator->sample = oscillator->sample + (freq / oscillator->sampleRate);
}

SawtoothOscillator *createSawtoothOscillator(float frequency, char* name, int sampleRate, int isOutput, int isCV) {
    SawtoothOscillator* oscillator = malloc(sizeof(SawtoothOscillator));
    oscillator->frequency = frequency;
    oscillator->name = name;
    oscillator->sampleRate = sampleRate;
    oscillator->isOutput = isOutput;
    oscillator->sample = 0;
    oscillator->isCV = isCV;
    oscillator->volume = 1;
    return oscillator;
}