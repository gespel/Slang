//
// Created by sten on 16.07.25.
//

#ifndef SQUARE_H
#define SQUARE_H
#include <stdlib.h>

typedef struct SquareOscillator {
    float* frequency;
    float* sample;
    float frequencyMultiplier;
    float volume;
    float phase;
    int sampleRate;
    char* name;
    int isOutput;
    int index;
} SquareOscillator;

SquareOscillator *createSquareOscillator(float* frequency, float frequencyMultiplier, char* name, int sampleRate, int isOutput);

float getSquareSample(SquareOscillator* oscillator);

#endif //SQUARE_H
