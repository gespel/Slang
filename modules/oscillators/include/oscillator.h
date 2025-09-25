
#ifndef SLANG_OSCILLATOR_H
#define SLANG_OSCILLATOR_H
#include "../../data/include/binaryData.h"
#include "wavetable.h"
#include "sawtooth.h"
#include "sine.h"
#include "square.h"
#include "triangle.h"
#include "oscillator_types.h"


Oscillator *createOscillator(void* data, OscillatorType type);

#endif