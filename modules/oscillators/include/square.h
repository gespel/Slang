//
// Created by sten on 16.07.25.
//

#ifndef SQUARE_H
#define SQUARE_H
#include <stdlib.h>

typedef struct SquareOscillator {
    double* frequency;
    double* sample;
    double frequencyMultiplier;
    double volume;
    double phase;
    int sampleRate;
    char* name;
    int isOutput;
    int index;
} SquareOscillator;

SquareOscillator *createSquareOscillator(double* frequency, double frequencyMultiplier, char* name, int sampleRate, int isOutput);

double getSquareSample(SquareOscillator* oscillator);

#endif //SQUARE_H
