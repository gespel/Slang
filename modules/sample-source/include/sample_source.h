#pragma once
//#include "include/rack.h"
#include "modules/oscillators/include/oscillator_types.h"
#include "modules/stepsequencer/include/stepsequencer_types.h"
#include "modules/stepsequencer/include/stepsequencer.h"
#include "modules/oscillators/include/oscillator.h"

typedef enum SampleSourceType {
    OSCILLATOR,
    STEPSEQUENCER,
    ENVELOPEGENERATOR
} SampleSourceType;

typedef struct SampleSource {
    char* name;
    void *sampleSource;
    SampleSourceType type;
    void **modifier;
    int numModifiers;
    int argumentIndex;
} SampleSource;

SampleSource* createSampleSource(char* name, void *sampleSource, SampleSourceType type, int argumentIndex);

float getSampleSourceOutputSample(SampleSource *ss);

float getSampleSourceSample(SampleSource *ss);

void printSampleSourceType(SampleSource* ss);