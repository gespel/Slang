//
// Created by Sten on 09.06.2025.
//
#include "../include/oscillator.h"

#include <stdio.h>

double getSineSample(SineOscillator* oscillator) {
    oscillator->phase += (oscillator->frequency[0] / oscillator->sampleRate) * 2.0 * M_PI;
    oscillator->sample[0] = sin(oscillator->phase);
    return oscillator->sample[0];
}
