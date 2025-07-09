
#ifndef SLANG_OSCILLATOR_H
#define SLANG_OSCILLATOR_H
#define M_PI 3.14159265358979323846
#include <math.h>
#include <string.h>
#include "binaryData.h"

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

typedef struct WavetableOscillator {
    double* frequency;
    double* sample;
    double frequencyMultiplier;
    double volume;
    int index;
    int wavetableLength;
    int sampleRate;
    char* name;
    float* waveTable;
    int isOutput;
} WavetableOscillator;

typedef struct SawtoothOscillator {
    double* frequency;
    double* sample;
    double frequencyMultiplier;
    double volume;
    double phase;
    int sampleRate;
    char* name;
    int isOutput;
} SawtoothOscillator;

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

double getSineSample(SineOscillator* oscillator);

double getWavetableSample(WavetableOscillator* oscillator);

double getSawtoothSample(SawtoothOscillator* oscillator);

double getSquareSample(SquareOscillator* oscillator);

#endif