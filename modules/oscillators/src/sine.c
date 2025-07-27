//
// Created by sten on 16.07.25.
//
#include "../include/sine.h"

float getSineSample(SineOscillator* oscillator) {
    oscillator->phase += (oscillator->frequency[0] * oscillator->frequencyMultiplier / oscillator->sampleRate) * 2.0 * M_PI;
    oscillator->sample[0] = sin(oscillator->phase);
    if (oscillator->isOutput == 1) {
        return oscillator->sample[0];
    }
    else {
        return 0.0;
    }
}

SineOscillator *createSineOscillator(float* frequency, float frequencyMultiplier, char* name, int sampleRate, int isOutput) {
    SineOscillator* osc = malloc(sizeof(SineOscillator));
    osc->isOutput = isOutput;
    osc->sample = malloc(sizeof(float));
    osc->name = name;
    osc->frequency = frequency;
    osc->frequencyMultiplier = frequencyMultiplier;
    osc->phase = 0.f;
    osc->sampleRate = sampleRate;
    return osc;
}