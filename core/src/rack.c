#include "core/include/rack.h"
#include "core/include/interpreter.h"
//#include "include/tools.h"
#include "core/include/tools.h"
#include "envelope/include/envelope_types.h"
#include "envelope/include/linenvelope.h"
#include "modules/filters/include/filter_types.h"
#include "modules/filters/include/lowpassfilter.h"
#include "modules/oscillators/include/oscillator_types.h"
#include "modules/oscillators/include/sawtooth.h"
#include "modules/oscillators/include/sine.h"
#include "modules/oscillators/include/square.h"
#include "modules/oscillators/include/triangle.h"
#include "modules/oscillators/include/wavetable.h"
#include "modules/sample-source/include/sample_source.h"
#include "modules/stepsequencer/include/stepsequencer.h"
#include "stepsequencer/include/stepsequencer_types.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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
                if (strcmp(rack->oscillators[i]->data->triangle->name, name) == 0) {
                    return rack->oscillators[i]->data->triangle;
                }
                break;
            case TERRAIN:
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
                rack->oscillators[i]->data->triangle->sampleRate = sampleRate;
                break;
            case TERRAIN:
                break;
        }
    }

}

void addOscillator(Rack* rack, Oscillator* input) {
    rack->oscillators[rack->numOscillators] = input;
    rack->numOscillators = rack->numOscillators + 1;
}

int getNumOscillators(Rack* rack) {
    int out = 0;
    for (int i = 0; i < rack->numSampleSources; i++) {
        if (rack->sampleSources[i]->type == OSCILLATOR) {
            out += 1;
        }
    }
    return out;
}

float getSample(Rack* rack) {
    float out = 0.f;
    float sample = 0.f;
    //printf("Number of sample sources: %d\n", rack->numSampleSources);

    updateSampleSources(rack);
    updateFilters(rack);

    for (int i = 0; i < rack->numSampleSources; i++) {
        sample = getSampleSourceOutputSample(rack->sampleSources[i]);
        //printSampleSourceType(rack->sampleSources[i]);
        //LOGDEBUG("sample: %f", sample);
        if (rack->sampleSources[i]->type != STEPSEQUENCER) {
            out += sample;
        }
    }

    for (int i = 0; i < rack->numFilters; i++) {
        Filter *filter = rack->filters[i];
        if (filter->type == LOWPASSFILTER) {
            LowPassFilter *lp = (LowPassFilter *) filter->filter;
            //recalculateFilterCoefficients(lp);
            out = processLowPassSample(lp, out);
        }
    }
    return out;
    //return normalizeSample(out, getNumOscillators(rack));
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

void updateSampleSources(Rack *rack) {
    for (int i = 0; i < rack->numSampleSources; i++) {
        SampleSource* ss = rack->sampleSources[i];
        if (ss->type == OSCILLATOR) {
            Oscillator *osc = (Oscillator *) ss->sampleSource;
            int ti = ss->argumentIndex;
            float freq = l3_expression(rack->interpreter, &ti);
            //LOGDEBUG("SampleSource id: %d Calculated new frequency: %f", i, freq);
            switch (osc->type) {
                case SINE: {
                    SineOscillator* so = osc->data->sine;
                    so->frequency = freq;
                    tickSineOscillator(so);
                    break;
                }
                case SAWTOOTH: {
                    SawtoothOscillator* wo = osc->data->sawtooth;
                    //LOGDEBUG("new frequency %f", wo->frequency);
                    wo->frequency = freq;
                    tickSawtoothOscillator(wo);
                    break;
                }
                case SQUARE: {
                    SquareOscillator* qo = osc->data->square;
                    qo->frequency = freq; 
                    tickSquareOscillator(qo);
                    break;
                }
                case WAVETABLE: {
                    WavetableOscillator* ao = osc->data->wavetable;
                    ao->frequency = freq;
                    break;
                }
                case TRIANGLE: {
                    TriangleOscillator* to = osc->data->triangle;
                    to->frequency = freq;
                    tickTriangleOscillator(to);
                    break;
                }
                default: {
                    break;
                }
            }
        }
        else if (ss->type == STEPSEQUENCER) {
            StepSequencer *seq = (StepSequencer *) ss->sampleSource;
            tickStepSequencer(seq);
        }
        else if (ss->type == ENVELOPEGENERATOR) {
            EnvelopeGenerator* env = (EnvelopeGenerator*)ss->sampleSource;
            LinearEnvelopeGenerator* lin = (LinearEnvelopeGenerator*)env->envelope;
            StepSequencer* step = env->triggerSequencer;
            if (step->trigger == 1) {
                triggerLinearEnvelopeGenerator(lin);
            }
            tickLinearEnvelopeGenerator(lin);
        }
    }
}

void updateFilters(Rack *rack) {
    for (int i = 0; i < rack->numFilters; i++) {
        Filter* filter = rack->filters[i];
        int ti = filter->argumentIndex;
        float freq = l3_expression(rack->interpreter, &ti);
        //LOGDEBUG("updated filter freq %f", freq);
        switch (filter->type) {
            case LOWPASSFILTER: {
                LowPassFilter* lp = filter->filter;
                updateCoefficients(lp, freq, rack->sampleRate[0]);
                break;
            }
            case HIGHPASSFILTER: {
                break;
            }
        }
    }
}

void updateEnvelopeGenerators(Rack *rack) {
    for (int i = 0; i < rack->numEnvelopeGenerators; i++) {
        EnvelopeGenerator* env = rack->envelopeGenerators[i];

        switch (env->type) {
            case LINENVELOPE:
                
                break;
            case EXPENVELOPE:
                break;
        }
    }
}

void addSampleSource(Rack* rack, SampleSource* input) {
    rack->sampleSources[rack->numSampleSources] = input;
    rack->numSampleSources = rack->numSampleSources + 1;
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

float normalizeSample(float sample, int numOscillators) {
    return sample / numOscillators;
}