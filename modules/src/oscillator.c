//
// Created by Sten on 09.06.2025.
//
#include "../include/oscillator.h"

#include <stdio.h>

double getSineSample(SineOscillator* oscillator) {
    oscillator->phase += (oscillator->frequency[0] * oscillator->frequencyMultiplier / oscillator->sampleRate) * 2.0 * M_PI;
    oscillator->sample[0] = sin(oscillator->phase);
    return oscillator->sample[0];
}

double getWavetableSample(WavetableOscillator* oscillator) {
    if (oscillator->index >= oscillator->wavetableLength) {
        oscillator->index = 0;
    }
    double out = oscillator->waveTable[oscillator->index];
    float temp = (float)oscillator->frequency[0] / 10;
    int n = (temp - floor(temp) > 0.5) ? ceil(temp) : floor(temp);
    oscillator->index += n;
    return out;
}