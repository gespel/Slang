//
// Created by sten on 16.07.25.
//

#ifndef SAWTOOTH_H
#define SAWTOOTH_H

typedef struct SawtoothOscillator {
    float* frequency;
    float* sample;
    float frequencyMultiplier;
    float volume;
    float phase;
    int sampleRate;
    char* name;
    int isOutput;
} SawtoothOscillator;

float getSawtoothSample(SawtoothOscillator* oscillator);

SawtoothOscillator *createSawtoothOscillator(float* frequency, float frequencyMultiplier, char* name, int sampleRate, int isOutput);

#endif //SAWTOOTH_H
