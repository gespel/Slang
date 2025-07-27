#include "../include/rack.h"

#include "tools.h"


void *getOscillator(Rack* rack, char* name) {
    for (int i = 0; i < rack->numOscillators; i++) {
        switch (rack->oscillators[i]->type) {
            case SINE:
                if (strcmp(rack->oscillators[i]->data->sine->name, name) == 0) {
                    return rack->oscillators[i]->data->sine;
                }
                break;
            case SAWTOOTH:
                if (strcmp(rack->oscillators[i]->data->sawtooth->name, name) == 0) {
                    return rack->oscillators[i]->data->sawtooth;
                }
                break;
            case SQUARE:
                if (strcmp(rack->oscillators[i]->data->square->name, name) == 0) {
                    return rack->oscillators[i]->data->square;
                }
                break;
            case WAVETABLE:
                if (strcmp(rack->oscillators[i]->data->wavetable->name, name) == 0) {
                    return rack->oscillators[i]->data->wavetable;
                }
                break;
        }
    }
    return NULL;
}

void setSampleRateForAllOscillators(Rack* rack, int sampleRate) {
    for (int i = 0; i < rack->numOscillators; i++) {
        switch (rack->oscillators[i]->type) {
            case SINE:
                rack->oscillators[i]->data->sine->sampleRate = sampleRate;
                break;
            case SAWTOOTH:
                rack->oscillators[i]->data->sawtooth->sampleRate = sampleRate;
                break;
            case SQUARE:
                rack->oscillators[i]->data->square->sampleRate = sampleRate;
                break;
            case WAVETABLE:
                rack->oscillators[i]->data->wavetable->sampleRate = sampleRate;
                break;
        }
    }

}

void addOscillator(Rack* rack, Oscillator* input) {
    rack->oscillators[rack->numOscillators] = input;
    rack->numOscillators = rack->numOscillators + 1;
}

float getSample(Rack* rack) {
    float out = 0.f;
    for (int i = 0; i < rack->numOscillators; i++) {
        switch (rack->oscillators[i]->type) {
            case SINE:
                out += getSineSample(rack->oscillators[i]->data->sine);
                break;
            case WAVETABLE:
                out += getWavetableSample(rack->oscillators[i]->data->wavetable);
                break;
            case SAWTOOTH:
                out += getSawtoothSample(rack->oscillators[i]->data->sawtooth);
                break;
            case SQUARE:
                out += getSquareSample(rack->oscillators[i]->data->square);
                break;
            default:
                out += 0;
                break;
        }
    }
    if (rack->numOscillators > 0) {
        out /= rack->numOscillators;
    }
    return out;
}