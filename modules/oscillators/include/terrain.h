#include "oscillator_types.h"

TerrainOscillator* createTerrainOscillator(
    float* frequency, 
    float frequencyMultiplier, 
    char* name, 
    float** terrain, 
    int terrainWidth, 
    int sampleRate, 
    int isOutput, 
    int isCV
);

float getTerrainSample(TerrainOscillator* terrainOscillator);

float** loadTerrainByName(char* terrainName);
