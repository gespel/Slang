//
// Created by Sten on 13.07.2025.
//

#ifndef WAVETABLE_H
#define WAVETABLE_H
#include <math.h>


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

double getWavetableSample(WavetableOscillator* oscillator);

WavetableOscillator* createWavetableOscillator(double* frequency, double frequencyMultiplier, char* name, float* waveTable, int wavetableLength, int sampleRate, int isOutput);

float* getWavetableByName(char* name);

#endif //WAVETABLE_H
