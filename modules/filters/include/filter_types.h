typedef enum {
    LOWPASSFILTER,
    HIGHPASSFILTER
} FilterType;

typedef struct Filter {
    FilterType type;
    void *filter;
} Filter;


typedef struct LowPassFilter {
    float cutoff;
} LowPassFilter;

typedef struct HighPassFilter {
    float cutoff;
} HighPassFilter;