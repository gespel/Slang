//
// Created by Sten on 20.07.2025.
//
#include "../include/oscillator.h"

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
    }
    return o;
}