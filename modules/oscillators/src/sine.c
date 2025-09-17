//
// Created by sten on 16.07.25.
//
#include "../include/sine.h"
#include <stdio.h>

float getSineSample(SineOscillator* oscillator) {
    //printf("freq: %f freqMul: %f\n", oscillator->frequency[0], oscillator->frequencyMultiplier);
    float freq = oscillator->frequency[0] * oscillator->frequencyMultiplier;
    if (freq < 0.0f) {
        freq = freq*(-1);
    }
    //printf("Calculated freq: %f\n", freq);
    oscillator->phase += (freq / oscillator->sampleRate) * 2.0 * M_PI;
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
    osc->sample[0] = 0.f;
    osc->name = name;
    osc->frequency = frequency;
    osc->frequencyMultiplier = frequencyMultiplier;
    osc->phase = 0.f;
    osc->sampleRate = sampleRate;
    return osc;
}