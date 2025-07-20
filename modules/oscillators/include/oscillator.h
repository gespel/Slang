
#ifndef SLANG_OSCILLATOR_H
#define SLANG_OSCILLATOR_H
#include "../../data/include/binaryData.h"
#include "wavetable.h"
#include "sawtooth.h"
#include "sine.h"
#include "square.h"

typedef enum OscillatorType {
    WAVETABLE, SQUARE, SAWTOOTH, SINE
} OscillatorType;

typedef union OscillatorData {
    WavetableOscillator* wavetable;
    SawtoothOscillator* sawtooth;
    SineOscillator* sine;
    SquareOscillator* square;
} OscillatorData;

typedef struct Oscillator {
    OscillatorType type;
    OscillatorData* data;
} Oscillator;


#endif