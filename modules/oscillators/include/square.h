//
// Created by sten on 16.07.25.
//

#ifndef SQUARE_H
#define SQUARE_H

typedef struct SquareOscillator {
    double* frequency;
    double* sample;
    double frequencyMultiplier;
    double volume;
    double phase;
    int sampleRate;
    char* name;
    int isOutput;
} SquareOscillator;

double getSquareSample(SquareOscillator* oscillator);

#endif //SQUARE_H
