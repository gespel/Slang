//
// Created by sten on 16.07.25.
//
#include "../include/sawtooth.h"
#include <stdio.h>

#include <stdlib.h>

float getSawtoothSample(SawtoothOscillator* oscillator) {
    if (oscillator->isCV == 1) {
        if (oscillator->sample[0] > 2) {
            oscillator->sample[0] = 0;
        }
    }
    else {
        if (oscillator->sample[0] > 1) {
            oscillator->sample[0] = -1.0;
        }
    }
    float freq = oscillator->frequency[0] * oscillator->frequencyMultiplier;
    oscillator->sample[0] = oscillator->sample[0] + (freq / oscillator->sampleRate);
    return oscillator->sample[0];
}

SawtoothOscillator *createSawtoothOscillator(float* frequency, float frequencyMultiplier, char* name, int sampleRate, int isOutput, int isCV) {
    SawtoothOscillator* oscillator = malloc(sizeof(SawtoothOscillator));
    oscillator->frequency = frequency;
    oscillator->frequencyMultiplier = frequencyMultiplier;
    oscillator->name = name;
    oscillator->sampleRate = sampleRate;
    oscillator->isOutput = isOutput;
    oscillator->sample = malloc(sizeof (float));
    oscillator->sample[0] = 0;
    oscillator->isCV = isCV;
    return oscillator;
}