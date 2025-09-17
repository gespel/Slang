#include "../include/rack.h"

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
                if (rack->oscillators[i]->data->sine->isOutput == 1) {
                    out += getSineSample(rack->oscillators[i]->data->sine);
                }
                else {
                    getSineSample(rack->oscillators[i]->data->sine);
                }
                break;
            case WAVETABLE:
                if (rack->oscillators[i]->data->wavetable->isOutput == 1) {
                    out += getWavetableSample(rack->oscillators[i]->data->wavetable);
                }
                else {
                    getWavetableSample(rack->oscillators[i]->data->wavetable);
                }
                break;
            case SAWTOOTH:
                if (rack->oscillators[i]->data->sawtooth->isOutput == 1) {
                    out += getSawtoothSample(rack->oscillators[i]->data->sawtooth);
                }
                else {
                    getSawtoothSample(rack->oscillators[i]->data->sawtooth);
                }
                break;
            case SQUARE:
                if (rack->oscillators[i]->data->square->isOutput == 1) {
                    out += getSquareSample(rack->oscillators[i]->data->square);
                }
                else {
                    getSquareSample(rack->oscillators[i]->data->square);
                }
                break;
            default:
                out += 0;
                break;
        }
    }
    if (rack->numOscillators > 0) {
        out /= rack->numOscillators;
    }

    for (int i = 0; i < rack->numSampleSources; i++) {
        if (rack->sampleSources[i]->type == STEPSEQUENCER) {
            StepSequencer *seq = (StepSequencer *) rack->sampleSources[i]->sampleSource;
            getStepSequencerSample(seq);
        }
    }

    return out;
}

SampleSource *getSampleSource(Rack* rack, char* name) {
    for (int i = 0; i < rack->numSampleSources; i++) {
        if (strcmp(rack->sampleSources[i]->name, name) == 0) {
            //printf("Found sample source with name %s\n", name);
            return rack->sampleSources[i];
        }
    }
    return NULL;
}

void addSampleSource(Rack* rack, SampleSource* input) {
    rack->sampleSources[rack->numSampleSources] = input;
    rack->numSampleSources = rack->numSampleSources + 1;
}

float *getSampleSourceSamplePtr(SampleSource *ss) {
    if (ss->type == OSCILLATOR) {
        Oscillator *osc = (Oscillator *) ss->sampleSource;
        switch (osc->type) {
            case SINE:
                return osc->data->sine->sample;
            case SAWTOOTH:
                return osc->data->sawtooth->sample;
            case SQUARE:
                return osc->data->square->sample;
            case WAVETABLE:
                return osc->data->wavetable->sample;
            default:
                return NULL;
        }
    }
    else if (ss->type == STEPSEQUENCER) {
        StepSequencer *seq = (StepSequencer *) ss->sampleSource;
        return &seq->sample;
    }
    return NULL;
}