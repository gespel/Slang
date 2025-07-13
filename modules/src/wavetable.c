//
// Created by Sten on 13.07.2025.
//
#include "wavetable.h"

#include <stdlib.h>

WavetableOscillator* createWavetableOscillator(
    double* frequency,
    double frequencyMultiplier,
    char* name,
    float* waveTable,
    int wavetableLength,
    int sampleRate,
    int isOutput) {

    WavetableOscillator* out = malloc(sizeof(WavetableOscillator));


    return out;
}
double getWavetableSample(WavetableOscillator* oscillator) {
    if (oscillator->index >= oscillator->wavetableLength) {
        oscillator->index = 0;
    }
    double out = oscillator->waveTable[oscillator->index];
    float temp = (float)oscillator->frequency[0] / 10;
    int n = (temp - floor(temp) > 0.5) ? ceil(temp) : floor(temp);
    oscillator->index += n;
    oscillator->sample[0] = out;
    if (oscillator->isOutput == 1) {
        return oscillator->sample[0];
    }
    else {
        return 0.0;
    }
}