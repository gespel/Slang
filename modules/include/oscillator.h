#ifndef SLANG_OSCILLATOR_H
#define SLANG_OSCILLATOR_H
#define M_PI 3.14159265358979323846
#include <math.h>
#include <string.h>

typedef struct SineOscillator {
    double* frequency;
    double* sample;
    double volume;
    double phase;
    int sampleRate;
    char* name;
} SineOscillator;

double getSineSample(SineOscillator* oscillator);

#endif
