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
            break;
        case SINE:
            o->data->sine = data;
            break;
        case SQUARE:
            o->data->square = data;
            break;
        case SAWTOOTH:
            o->data->sawtooth = data;
            break;
    }
    o->type = WAVETABLE;
    return o;
}