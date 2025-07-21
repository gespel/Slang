//
// Created by sten on 16.07.25.
//
#include "../include/sawtooth.h"

#include <stdlib.h>

double getSawtoothSample(SawtoothOscillator* oscillator) {
    if (oscillator->sample[0] >= 1) {
        oscillator->sample[0] = -1.0;
    }
    oscillator->sample[0] = oscillator->sample[0] + (oscillator->frequency[0] / oscillator->sampleRate);
    return oscillator->sample[0];
}

SawtoothOscillator *createSawtoothOscillator(double* frequency, double frequencyMultiplier, char* name, int sampleRate, int isOutput) {
    SawtoothOscillator* oscillator = malloc(sizeof(SawtoothOscillator));
    oscillator->frequency = frequency;
    oscillator->frequencyMultiplier = frequencyMultiplier;
    oscillator->name = name;
    oscillator->sampleRate = sampleRate;
    oscillator->isOutput = isOutput;
    oscillator->sample = malloc(sizeof (double));
    oscillator->sample[0] = 0;
    return oscillator;
}