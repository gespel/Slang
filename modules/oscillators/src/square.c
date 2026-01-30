//
// Created by sten on 16.07.25.
//
#include "modules/oscillators/include/square.h"

SquareOscillator *createSquareOscillator(float frequency, char* name, int sampleRate, int isOutput, int isCV) {
    SquareOscillator* oscillator = malloc(sizeof(SquareOscillator));
    oscillator->frequency = frequency;
    oscillator->name = name;
    oscillator->sampleRate = sampleRate;
    oscillator->isCV = isCV;
    oscillator->isOutput = isOutput;
    oscillator->sample = 0;
    oscillator->index = 0;
    oscillator->volume = 1;
    return oscillator;
}

void tickSquareOscillator(SquareOscillator *oscillator) {
    float out = 0;
    if (oscillator->index >= (oscillator->sampleRate / oscillator->frequency)) {
        oscillator->index = 0;
    }

    if (oscillator->index >= ((float)oscillator->sampleRate/oscillator->frequency) / 2) {
        out = 1;
    }
    else {
        out = -1;
    }
    oscillator->sample = out;
    oscillator->index++;
}

float getSquareSample(SquareOscillator* oscillator) {
    if (oscillator->isCV == 1) {
        oscillator->sample = oscillator->sample + 1.0;
    }
    if (oscillator->isOutput == 1) {
        return oscillator->sample * oscillator->volume;
    }
    else {
        return 0.0;
    }
}