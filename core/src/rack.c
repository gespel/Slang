#include "../include/rack.h"

Rack* createRack(int* sampleRate, int* bufferSize) {
    Rack* rack = malloc(sizeof(Rack));
    rack->sampleRate = sampleRate;
    rack->bufferSize = bufferSize;
    rack->oscillators = malloc(sizeof(Oscillator*) * 128);
    memset(rack->oscillators, 0, sizeof(Oscillator*) * 128);
    rack->numOscillators = 0;
    rack->stepSequencers = malloc(sizeof(StepSequencer*) * 128);
    memset(rack->stepSequencers, 0, sizeof(StepSequencer*) * 128);
    rack->numStepSequencers = 0;
    rack->sampleSources = malloc(sizeof(SampleSource*) * 128);
    memset(rack->sampleSources, 0, sizeof(SampleSource*) * 128);
    rack->numSampleSources = 0;
    rack->filters = malloc(sizeof(Filter*) * 128);
    memset(rack->filters, 0, sizeof(Filter*) * 128);
    rack->numFilters = 0;
    return rack;
}

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
            case TRIANGLE:
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
            case TRIANGLE:
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
    //printf("Number of sample sources: %d\n", rack->numSampleSources);
    for (int i = 0; i < rack->numSampleSources; i++) {
        if (rack->sampleSources[i]->type == STEPSEQUENCER) {
            StepSequencer *seq = (StepSequencer *) rack->sampleSources[i]->sampleSource;
            //LOGINFO("Adding step sequencer sample: %f", seq->sample);
            getStepSequencerSample(seq);
        }
        else if (rack->sampleSources[i]->type == OSCILLATOR) {
            Oscillator *osc = (Oscillator *) rack->sampleSources[i]->sampleSource;
            switch (osc->type) {
                case SINE:
                    if (osc->data->sine->isOutput == 1) {
                        out += getSineSample(osc->data->sine);
                    }
                    else {
                        getSineSample(osc->data->sine);
                    }
                    break;
                case SAWTOOTH:
                    if (osc->data->sawtooth->isOutput == 1) {
                        out += getSawtoothSample(osc->data->sawtooth);
                    }
                    else {
                        getSawtoothSample(osc->data->sawtooth);
                    }
                    break;
                case SQUARE:
                    if (osc->data->square->isOutput == 1) {
                        out += getSquareSample(osc->data->square);
                    }
                    else {
                        getSquareSample(osc->data->square);
                    }
                    break;
                case WAVETABLE:
                    if (osc->data->wavetable->isOutput == 1) {
                        out += getWavetableSample(osc->data->wavetable);
                    }
                    else {
                        getWavetableSample(osc->data->wavetable);
                    }
                    break;
                default:
                    break;
            }
        }

        for (int j = 0; j < rack->sampleSources[i]->numModifiers; j++) {
            SampleSource *sampleSource = rack->sampleSources[i];
            Modifier *modifier = sampleSource->modifier[j];
            
            switch (modifier->type) {
                case FILTER:
                    Filter *f = modifier->modifier;
                    if (f->type == LOWPASSFILTER) {
                        LowPassFilter *lp = f->filter;
                        recalculateFilterCoefficients(lp);
                        out = processLowPassSample(lp, out);
                    }
                    break;
                case BITCRUSHER:
                    break;
            } 
        }

    }
    for (int i = 0; i < rack->numFilters; i++) {
        Filter *filter = rack->filters[i];
        if (filter->type == LOWPASSFILTER) {
            LowPassFilter *lp = (LowPassFilter *) filter->filter;
            out = processLowPassSample(lp, out);
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

void addModifierToSampleSource(Rack *rack, char *name, void *modifier) {
    for (int i = 0; i < rack->numSampleSources; i++) {
        if (strcmp(name, rack->sampleSources[i]->name) == 0) {
            rack->sampleSources[i]->modifier[rack->sampleSources[i]->numModifiers] = modifier;
            rack->sampleSources[i]->numModifiers += 1;
        }
    }
}

void addFilter(Rack* rack, Filter* input) {
    rack->filters[rack->numFilters] = input;
    rack->numFilters = rack->numFilters + 1;
}