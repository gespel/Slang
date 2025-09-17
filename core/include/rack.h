#ifndef SLANG_RACK_H
#define SLANG_RACK_H
#include "../../modules/oscillators/include/oscillator.h"
#include "../../modules/stepsequencer/include/stepsequencer.h"
#include "../../modules/data/include/binaryData.h"
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "core_types.h"

void *getOscillator(Rack* rack, char* name);

void *getSampleSource(Rack* rack, char* name);

void setSampleRateForAllOscillators(Rack* rack, int sampleRate);

void addOscillator(Rack* rack, Oscillator* input);

void addStepSequencer(Rack* rack, StepSequencer* input);

float getSample(Rack* rack);

#endif
