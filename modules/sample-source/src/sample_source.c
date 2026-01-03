#include "sample-source/include/sample_source.h"

SampleSource* createSampleSource(char* name, void *sampleSource, SampleSourceType type, int argumentIndex) {
    SampleSource *out = malloc(sizeof(SampleSource));
    out->name = name;
    out->sampleSource = sampleSource;
    out->type = type;
    out->numModifiers = 0;
    out->modifier = malloc(8192);
    out->argumentIndex = argumentIndex;
    return out;
}

float getSampleSourceSample(SampleSource *ss) {
    float out = 0;
    float sample = 0;
    if (ss->type == OSCILLATOR) {
        Oscillator *osc = (Oscillator *) ss->sampleSource;
        switch (osc->type) {
            case SINE:
                sample = getSineSample(osc->data->sine);
                if (osc->data->sine->isOutput == 1) {
                    out += sample;
                }
                break;
            case SAWTOOTH:
                sample = getSawtoothSample(osc->data->sawtooth);
                printf("%f\n", sample);
                if (osc->data->sawtooth->isOutput == 1) {
                    out += sample;
                }
                break;
            case SQUARE:
                sample = getSquareSample(osc->data->square);
                if (osc->data->square->isOutput == 1) {
                    out += sample;
                }
                break;
            case WAVETABLE:
                sample = getWavetableSample(osc->data->wavetable);
                if (osc->data->wavetable->isOutput == 1) {
                    out += sample;
                }
                break;
            case TRIANGLE:
                sample = getTriangleSample(osc->data->triangle);
                if (osc->data->triangle->isOutput == 1) {
                    out += sample;
                }
            default:
                break;
        }
    }
    else if (ss->type == STEPSEQUENCER) {
        StepSequencer *seq = (StepSequencer *) ss->sampleSource;
        return seq->sample;
    }
    return out;
}