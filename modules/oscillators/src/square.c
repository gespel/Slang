//
// Created by sten on 16.07.25.
//
#include "../include/square.h"

SquareOscillator *createSquareOscillator(double* frequency, double frequencyMultiplier, char* name, int sampleRate, int isOutput) {
    SquareOscillator* oscillator = malloc(sizeof(SquareOscillator));
    oscillator->frequency = frequency;
    oscillator->frequencyMultiplier = frequencyMultiplier;
    oscillator->name = name;
    oscillator->sampleRate = sampleRate;
    oscillator->isOutput = isOutput;
    oscillator->sample = malloc(sizeof (double));
    oscillator->sample[0] = 0;
    oscillator->index = 0;
    return oscillator;
}

double getSquareSample(SquareOscillator* oscillator) {
    double out = 0;
    if (oscillator->index >= (oscillator->sampleRate / oscillator->frequency[0])) {
        oscillator->index = 0;
    }

    if (oscillator->index >= ((double)oscillator->sampleRate/oscillator->frequency[0]) / 2) {
        out = 1;
    }
    else {
        out = -1;
    }
    oscillator->index++;
    return out;
}