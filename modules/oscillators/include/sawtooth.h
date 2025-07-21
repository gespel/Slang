//
// Created by sten on 16.07.25.
//

#ifndef SAWTOOTH_H
#define SAWTOOTH_H

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

double getSawtoothSample(SawtoothOscillator* oscillator);

SawtoothOscillator *createSawtoothOscillator(double* frequency, double frequencyMultiplier, char* name, int sampleRate, int isOutput);

#endif //SAWTOOTH_H
