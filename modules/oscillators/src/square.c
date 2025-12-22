//
// Created by sten on 16.07.25.
//
#include "oscillators/include/square.h"

SquareOscillator *createSquareOscillator(float* frequency, float frequencyMultiplier, char* name, int sampleRate, int isOutput, int isCV) {
    SquareOscillator* oscillator = malloc(sizeof(SquareOscillator));
    oscillator->frequency = frequency;
    oscillator->frequencyMultiplier = frequencyMultiplier;
    oscillator->name = name;
    oscillator->sampleRate = sampleRate;
    oscillator->isCV = isCV;
    oscillator->isOutput = isOutput;
    oscillator->sample = malloc(sizeof (float));
    oscillator->sample[0] = 0;
    oscillator->index = 0;
    return oscillator;
}

float getSquareSample(SquareOscillator* oscillator) {
    float out = 0;
    if (oscillator->index >= (oscillator->sampleRate / oscillator->frequency[0])) {
        oscillator->index = 0;
    }

    if (oscillator->index >= ((float)oscillator->sampleRate/oscillator->frequency[0]) / 2) {
        out = 1;
    }
    else {
        out = -1;
    }
    oscillator->sample[0] = out;
    oscillator->index++;

    if (oscillator->isCV == 1) {
        oscillator->sample[0] = oscillator->sample[0] + 1.0;
    }
    if (oscillator->isOutput == 1) {
        return oscillator->sample[0];
    }
    else {
        return 0.0;
    }
}