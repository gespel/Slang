//
// Created by sten on 16.07.25.
//
#include "oscillators/include/sine.h"

void tickSineOscillator(SineOscillator *oscillator) {
    float freq = oscillator->frequency;
    if (freq < 0.0f) {
        freq = freq*(-1);
    }
    //printf("Calculated freq: %f\n", freq);
    oscillator->phase += (freq / oscillator->sampleRate) * 2.0 * M_PI;
    oscillator->sample = sin(oscillator->phase);
    
}

float getSineSample(SineOscillator* oscillator) {
    //printf("freq: %f freqMul: %f\n", oscillator->frequency[0], oscillator->frequencyMultiplier);
    if (oscillator->isCV == 1) {
        oscillator->sample = oscillator->sample + 1.0;
    }
    if (oscillator->isOutput == 1) {
        return oscillator->sample * oscillator->volume;
    }
    else {
        return 0.0;
    }
}

SineOscillator *createSineOscillator(float frequency, char* name, int sampleRate, int isOutput, int isCV) {
    SineOscillator* osc = malloc(sizeof(SineOscillator));
    osc->isOutput = isOutput;
    osc->sample = 0.f;
    osc->name = name;
    osc->frequency = frequency;
    osc->phase = 0.f;
    osc->sampleRate = sampleRate;
    osc->isCV = isCV;
    osc->volume = 1;
    return osc;
}