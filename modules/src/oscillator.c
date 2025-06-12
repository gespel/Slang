//
// Created by Sten on 09.06.2025.
//
#include "../include/oscillator.h"

#include <stdio.h>

double getSample(SineOscillator* oscillator) {
    oscillator->phase += (oscillator->frequency[0] / oscillator->sampleRate) * 2.0 * M_PI;
    //double* sample;
    //*sample = oscillator->phase;
    return sin(oscillator->phase);
}
