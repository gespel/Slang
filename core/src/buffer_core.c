//
// Created by Sten on 07.06.2025.
//
#include "../include/buffer_core.h"

SlangBufferCore* createBufferCore(SlangInterpreter* si, int bufferSize) {
    SlangBufferCore* bufferCore = malloc(sizeof(SlangBufferCore));
    bufferCore->interpreter = si;
    bufferCore->buffer = malloc(sizeof(double) * bufferSize);
    return bufferCore;
}

double* renderBuffer(SlangBufferCore* sbc) {
    Rack* rack = sbc->interpreter->main_rack;
    double* out = malloc(sizeof(double) * rack->bufferSize);
    for (int sample = 0; sample < rack->bufferSize; sample++) {
        double temp = 0;
        for (int ss = 0; ss < rack->numSineOscillators; ss++) {
            temp += getSample(rack->sine_oscillators[ss]);

        }
		temp /= rack->numSineOscillators;
        out[sample] = temp;
    }
    sbc->buffer = out;
    return out;
}