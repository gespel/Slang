//
// Created by sten on 16.07.25.
//
#include "../include/sawtooth.h"

double getSawtoothSample(SawtoothOscillator* oscillator) {
    if (oscillator->sample[0] >= 1) {
        oscillator->sample[0] = -1.0;
    }
    oscillator->sample[0] = oscillator->sample[0] + (oscillator->frequency[0] / oscillator->sampleRate);
    return oscillator->sample[0];
}