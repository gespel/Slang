//
// Created by Sten on 09.08.2025.
//

#ifndef OSCILLATOR_TYPES_H
#define OSCILLATOR_TYPES_H

typedef struct WavetableOscillator {
    float frequency;
    float sample;
    float volume;
    int index;
    int wavetableLength;
    int sampleRate;
    char* name;
    float* waveTable;
    int isOutput;
    int isCV;
} WavetableOscillator;

typedef struct SawtoothOscillator {
    float frequency;
    float sample;
    float volume;
    float phase;
    int sampleRate;
    char* name;
    int isOutput;
    int isCV;
} SawtoothOscillator;

typedef struct SquareOscillator {
    float frequency;
    float sample;
    float volume;
    float phase;
    int sampleRate;
    char* name;
    int isOutput;
    int index;
    int isCV;
} SquareOscillator;

typedef struct SineOscillator {
    float frequency;
    float sample;
    float volume;
    float phase;
    int sampleRate;
    char* name;
    int isOutput;
    int isCV;
} SineOscillator;

typedef struct TriangleOscillator {
    float frequency;
    float sample;
    float volume;
    float phase;
    int sampleRate;
    char *name;
    int isOutput;
    int isCV;
} TriangleOscillator;

typedef struct TerrainOscillator {
    float frequency;
    float sample;
    float volume;
    float phase;
    int sampleRate;
    char *name;
    int terrainSize;
    int wavetableSize;
    int terrainIndex;
    int wavetableIndex;
    float **terrain;
    int isOutput;
    int isCV;
} TerrainOscillator;

typedef enum OscillatorType {
    WAVETABLE, SQUARE, SAWTOOTH, SINE, TRIANGLE, TERRAIN
} OscillatorType;

typedef union OscillatorData {
    WavetableOscillator* wavetable;
    SawtoothOscillator* sawtooth;
    SineOscillator* sine;
    SquareOscillator* square;
    TriangleOscillator* triangle;
    TerrainOscillator* terrain;
} OscillatorData;

typedef struct Oscillator {
    OscillatorType type;
    OscillatorData* data;
} Oscillator;

#endif //OSCILLATOR_TYPES_H
