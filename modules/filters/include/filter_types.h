#ifndef FILTER_TYPES_H
#define FILTER_TYPES_H
typedef enum {
    LOWPASSFILTER,
    HIGHPASSFILTER
} FilterType;

typedef struct Filter {
    FilterType type;
    void *filter;
    int argumentIndex;
} Filter;


typedef struct LowPassFilter {
    float cutoff;
    float dt;
    float RC;
    float alpha;
    float currentInput;
    float currentOutput;
    int sampleRate;
} LowPassFilter;

typedef struct HighPassFilter {
    float cutoff;
    float dt;
    float RC;
    float alpha;
    float currentInput;
    float currentOutput;
} HighPassFilter;
#endif // FILTER_TYPES_H