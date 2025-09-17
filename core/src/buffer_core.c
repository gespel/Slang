//
// Created by Sten on 07.06.2025.
//
#include "../include/buffer_core.h"

SlangBufferCore* createBufferCore(SlangInterpreter* si, int sampleRate, int bufferSize) {
    SlangBufferCore* bufferCore = malloc(sizeof(SlangBufferCore));
    bufferCore->interpreter = si;
    bufferCore->bufferSize = bufferSize;
    bufferCore->sampleRate = sampleRate;
    bufferCore->interpreter->main_rack->bufferSize = &bufferCore->bufferSize;
    bufferCore->interpreter->main_rack->sampleRate = &bufferCore->sampleRate;
    bufferCore->buffer = malloc(sizeof(float) * bufferSize);
    setSampleRateForAllOscillators(bufferCore->interpreter->main_rack, sampleRate);
    si->sampleRate = sampleRate;
    return bufferCore;
}

void destroyBufferCore(SlangBufferCore* sbc) {
    if (sbc) {
        if (sbc->buffer) {
            free(sbc->buffer);
        }
        free(sbc);
    }
}

float* renderBuffer(SlangBufferCore* sbc) {
    Rack* rack = sbc->interpreter->main_rack;
    if (!rack || !sbc->interpreter) {
        return NULL;
    }
    if (sbc->bufferSize <= 0) {
        return NULL;
    }
    if (sbc->sampleRate <= 0) {
        return NULL;
    }
    
    float* out = malloc(sizeof(float) * sbc->bufferSize);
    for (int sample = 0; sample < sbc->bufferSize; sample++) {
        out[sample] = getSample(rack);
    }
    sbc->buffer = out;
    return out;
}
