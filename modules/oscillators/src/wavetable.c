//
// Created by Sten on 13.07.2025.
//
#include "../include/wavetable.h"

WavetableOscillator* createWavetableOscillator(
    float* frequency,
    float frequencyMultiplier,
    char* name,
    float* waveTable,
    int wavetableLength,
    int sampleRate,
    int isOutput) {

    WavetableOscillator* out = malloc(sizeof(WavetableOscillator));
    out->frequency = frequency;
    out->frequencyMultiplier = frequencyMultiplier;
    out->name = name;
    out->waveTable = waveTable;
    out->wavetableLength = wavetableLength;
    out->sampleRate = sampleRate;
    out->isOutput = isOutput;
    out->index = 0;
    out->sample = malloc(sizeof(float));
    return out;
}
float getWavetableSample(WavetableOscillator* oscillator) {
    if (oscillator->index >= oscillator->wavetableLength) {
        oscillator->index = 0;
    }
    float out = oscillator->waveTable[oscillator->index];
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

float* getWavetableByName(char* name) {
    if (strcmp("strangeone", name) == 0) {
        return random_wave_one;
    }
    if (strcmp("strangetwo", name) == 0) {
        return random_wave_two;
    }
    if (strcmp("strangethree", name) == 0) {
        return random_wave_three;
    }
    if (strcmp("strangefour", name) == 0) {
        return random_wave_four;
    }
    if (strcmp("sine", name) == 0) {
        return sine_wave;
    }

    return NULL;
}