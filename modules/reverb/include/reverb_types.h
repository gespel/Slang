#ifndef REVERB_TYPES_H
#define REVERB_TYPES_H
typedef enum ReverbType {
    SPRINGREVERB
} ReverbType;

typedef struct Reverb {
    void *reverb;
    ReverbType type;
} Reverb;

typedef struct SpringReverb {

} SpringReverb;
#endif // REVERB_TYPES_H