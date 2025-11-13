#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../data/include/binaryData.h"
#include "oscillator_types.h"
#include <errno.h>
#include <locale.h>
#define TERRAIN_FILE_PATH "waves"


TerrainOscillator* createTerrainOscillator(
    float* frequency, 
    float frequencyMultiplier, 
    char* name, 
    float** terrain, 
    int terrainWidth, 
    int terrainIndex,
    int wavetableIndex,
    int sampleRate, 
    int isOutput, 
    int isCV
);

float getTerrainSample(TerrainOscillator* terrainOscillator);

float** loadTerrainByName(char* terrainName);
