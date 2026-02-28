#include "modules/filters/include/filter.h"
#include "modules/filters/include/filter_types.h"
#include "modules/filters/include/lowpassfilter.h"
#include "stdlib.h"

Filter *createFilter(void* filter, FilterType type) {
    Filter *out = malloc(sizeof(Filter));
    out->filter = filter;
    out->type = type;
    return out;
}

float processFilterSample(Filter *filter, float sample) {
    if (filter->type == LOWPASSFILTER) {
        return processLowPassSample(filter->filter, sample);
    }
    else if (filter->type == HIGHPASSFILTER) {
        
    }
    return 0.0f;
}