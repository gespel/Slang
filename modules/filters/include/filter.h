#include "modules/filters/include/filter_types.h"

Filter *createFilter(void* filter, FilterType type);

float processFilterSample(Filter *filter, float sample);