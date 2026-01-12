//
// Created by Sten on 07.06.2025.
//
#include "core/include/buffer_core.h"
#include "core/include/rack.h"
#include "core/include/tools.h"

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
    si->bufferSize = bufferSize;

    if (si->interpretedCount > 0) {
        LOGERROR("Do not create the BufferCore AFTER you interpreted the tokens!");
        exit(-1);
    }
    LOGINFO("Creating Slang Buffer Core with a sample rate of %i and a buffer size of %i", sampleRate, bufferSize);

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
    if(sbc->buffer) {
        free(sbc->buffer);
    }
    Rack* rack = sbc->interpreter->main_rack;
    
    float* out = malloc(sizeof(float) * sbc->bufferSize);
    for (int sample = 0; sample < sbc->bufferSize; sample++) {
        float s = getSample(rack);
        //printf("%f\n", s);
        out[sample] = s;
    }
    sbc->buffer = out;
    return out;
}
