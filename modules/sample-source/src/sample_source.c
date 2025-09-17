#include "../include/sample_source.h"

SampleSource* createSampleSource(char* name, void *sampleSource, SampleSourceType type) {
    SampleSource *out = malloc(sizeof(SampleSource));
    out->name = name;
    out->sampleSource = sampleSource;
    out->type = type;
    return out;
}