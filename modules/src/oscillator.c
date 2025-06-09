//
// Created by Sten on 09.06.2025.
//
#include "../include/oscillator.h"

#include <stdio.h>

double getSample(SineOscillator* oscillator) {
    oscillator->phase += (oscillator->frequency / oscillator->sampleRate) * 2.0 * M_PI;
    return sin(oscillator->phase);
}
