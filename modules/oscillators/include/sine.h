//
// Created by sten on 16.07.25.
//

#ifndef SINE_H
#define SINE_H
#define M_PI 3.14159265358979323846
#include <math.h>
#include <stdlib.h>

typedef struct SineOscillator {
    double* frequency;
    double* sample;
    double frequencyMultiplier;
    double volume;
    double phase;
    int sampleRate;
    char* name;
    int isOutput;
} SineOscillator;

double getSineSample(SineOscillator* oscillator);

SineOscillator *createSineOscillator(double* frequency, double frequencyMultiplier, char* name, int sampleRate, int isOutput);

#endif //SINE_H
