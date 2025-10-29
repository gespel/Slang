#pragma once
#include "../../oscillators/include/oscillator_types.h"
#include "../../stepsequencer/include/stepsequencer_types.h"
#include "../../stepsequencer/include/stepsequencer.h"
#include "../../oscillators/include/oscillator.h"

typedef enum SampleSourceType {
    OSCILLATOR,
    STEPSEQUENCER,
} SampleSourceType;

typedef struct SampleSource {
    char* name;
    void *sampleSource;
    SampleSourceType type;
    void **modifier;
    int numModifiers;
} SampleSource;

SampleSource* createSampleSource(char* name, void *sampleSource, SampleSourceType type);