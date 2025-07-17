//
// Created by sten on 16.07.25.
//
#include "../include/sine.h"

double getSineSample(SineOscillator* oscillator) {
    oscillator->phase += (oscillator->frequency[0] * oscillator->frequencyMultiplier / oscillator->sampleRate) * 2.0 * M_PI;
    oscillator->sample[0] = sin(oscillator->phase);
    if (oscillator->isOutput == 1) {
        return oscillator->sample[0];
    }
    else {
        return 0.0;
    }
}