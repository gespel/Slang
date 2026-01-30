#include "modules/oscillators/include/terrain.h"

float getTerrainSample(TerrainOscillator* terrainOscillator) {
    float out = 0;
    out = terrainOscillator->terrain[terrainOscillator->terrainIndex][terrainOscillator->wavetableIndex];
    
    terrainOscillator->wavetableIndex += 1;
    if (terrainOscillator->wavetableIndex >= terrainOscillator->wavetableSize) {
        terrainOscillator->wavetableIndex = 0;
    }
    
    return out;
}

float** loadTerrainByName(char* terrainName) {
#ifndef SLANGONIC
    int x = 128;

    setlocale(LC_NUMERIC, "C");  // <-- das ist der Schlüssel
    char *line = NULL;
    size_t read;
    size_t len;
    float** out = malloc(sizeof(float*) * 128);
    
    for(int i = 0; i < x; i++) {
        out = malloc(sizeof(float) * 48000);
    }

    char path[512];
    snprintf(path, 512, "%s/%s.sterrain", TERRAIN_FILE_PATH, terrainName);

    FILE *fp = fopen(path, "r");
    if (!fp) { 
        perror("fopen"); 
        return NULL; 
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        char* pch;
        pch = strtok(line, " ,;");
        while(pch != NULL) {
            printf("%s\n", pch);
            pch = strtok(NULL, " ,;");
        }
    }

    free(line);
    fclose(fp);
    return out;
#endif
}