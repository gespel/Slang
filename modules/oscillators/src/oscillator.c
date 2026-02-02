//
// Created by Sten on 20.07.2025.
//
#include "modules/oscillators/include/oscillator.h"
#include "modules/oscillators/include/oscillator_types.h"

Oscillator *createOscillator(void* data, OscillatorType type) {
    Oscillator *o = malloc(sizeof(Oscillator));
    o->data = malloc(sizeof(OscillatorData));
    switch (type) {
        case WAVETABLE:
            o->data->wavetable = data;
            o->type = WAVETABLE;
            break;
        case SINE:
            o->data->sine = data;
            o->type = SINE;
            break;
        case SQUARE:
            o->data->square = data;
            o->type = SQUARE;
            break;
        case SAWTOOTH:
            o->data->sawtooth = data;
            o->type = SAWTOOTH;
            break;
        case TRIANGLE:
            o->data->triangle = data;
            o->type = TRIANGLE;
            break;
        case RANDOM_OSC_TYPE:
            o->data->random = data;
            o->type = RANDOM_OSC_TYPE;
            break;
        case TERRAIN:
            break;
    }
    return o;
}