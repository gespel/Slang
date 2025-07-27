//
// Created by sten on 16.07.25.
//

#ifndef SINE_H
#define SINE_H
#define M_PI 3.14159265358979323846
#include <math.h>
#include <stdlib.h>

typedef struct SineOscillator {
    float* frequency;
    float* sample;
    float frequencyMultiplier;
    float volume;
    float phase;
    int sampleRate;
    char* name;
    int isOutput;
} SineOscillator;

float getSineSample(SineOscillator* oscillator);

SineOscillator *createSineOscillator(float* frequency, float frequencyMultiplier, char* name, int sampleRate, int isOutput);

#endif //SINE_H
