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
    bufferCore->buffer = malloc(sizeof(double) * bufferSize);
    setSampleRateForAllOscillators(bufferCore->interpreter->main_rack, sampleRate);
    return bufferCore;
}

double* renderBuffer(SlangBufferCore* sbc) {
    Rack* rack = sbc->interpreter->main_rack;
    double* out = malloc(sizeof(double) * sbc->bufferSize);
    for (int sample = 0; sample < sbc->bufferSize; sample++) {

        double temp = 0;
        for (int ss = 0; ss < rack->numSineOscillators; ss++) {
            temp += getSineSample(rack->sine_oscillators[ss]);

        }
        if(rack->numSineOscillators != 0) {
		    temp /= rack->numSineOscillators;
        }
        //else {
        //    temp = 0;
        //}

        for (int ws = 0; ws < rack->numWaveOscillators; ws++) {
            temp += getWavetableSample(rack->wave_oscillators[ws]);
        }
        if(rack->numWaveOscillators != 0) {
            temp /= rack->numWaveOscillators;
        }
        //else {
        //    temp = 0;
        //}
        out[sample] = temp;
    }
    sbc->buffer = out;
    return out;
}