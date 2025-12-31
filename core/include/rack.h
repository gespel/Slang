#ifndef SLANG_RACK_H
#define SLANG_RACK_H
#include "modules/modules.h"
#include <stdlib.h>
#include <stdio.h>
#include "core_types.h"

Rack* createRack(int* sampleRate, int* bufferSize);

void *getOscillator(Rack* rack, char* name);

SampleSource *getSampleSource(Rack* rack, char* name);

float getSampleSourceSample(SampleSource *ss);

void updateSampleSources(Rack* rack);

void setSampleRateForAllOscillators(Rack* rack, int sampleRate);

void addOscillator(Rack* rack, Oscillator* input);

void addStepSequencer(Rack* rack, StepSequencer* input);

void addSampleSource(Rack* rack, SampleSource* input);

void addFilter(Rack* rack, Filter* input);

void addModifierToSampleSource(Rack *rack, char *name, void *modifier);

float getSample(Rack* rack);

#endif
