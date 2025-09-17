#pragma once
#include "../../oscillators/include/oscillator_types.h"
#include "../../stepsequencer/include/stepsequencer_types.h"
#include "../../oscillators/include/oscillator.h"

typedef enum SampleSourceType {
    OSCILLATOR,
    STEPSEQUENCER,
} SampleSourceType;

typedef struct SampleSource {
    void *sampleSource;
    SampleSourceType type;
} SampleSource;

SampleSource* createSampleSource(void *sampleSource, SampleSourceType type);