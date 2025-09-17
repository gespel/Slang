#include "../include/sample_source.h"

SampleSource* createSampleSource(void *sampleSource, SampleSourceType type) {
    SampleSource *out = malloc(sizeof(SampleSource));
    out->sampleSource = sampleSource;
    out->type = type;
    return out;
}