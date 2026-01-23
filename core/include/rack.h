#ifndef SLANG_RACK_H
#define SLANG_RACK_H
#include "modules/envelope/include/envelope_types.h"
#include "modules/modules.h"
#include <stdlib.h>
#include <stdio.h>
#include "core_types.h"

Rack* createRack(int* sampleRate, int* bufferSize);

void *getOscillator(Rack* rack, char* name);

SampleSource *getSampleSource(Rack* rack, char* name);

void updateSampleSources(Rack* rack);

void updateFilters(Rack* rack);

void updateEnvelopeGenerators(Rack* rack);

void setSampleRateForAllOscillators(Rack* rack, int sampleRate);

void addOscillator(Rack* rack, Oscillator* input);

int getNumOscillators(Rack* rack);

void addStepSequencer(Rack* rack, StepSequencer* input);

void addSampleSource(Rack* rack, SampleSource* input);

void addFilter(Rack* rack, Filter* input);

void addModifierToSampleSource(Rack *rack, char *name, void *modifier);

float getSample(Rack* rack);

float normalizeSample(float sample, int numOscillators);

#endif
