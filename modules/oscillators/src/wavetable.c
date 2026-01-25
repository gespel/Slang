//
// Created by Sten on 13.07.2025.
//
#include "oscillators/include/wavetable.h"

WavetableOscillator* createWavetableOscillator(
    float frequency,
    char* name,
    float* waveTable,
    int wavetableLength,
    int sampleRate,
    int isOutput,
    int isCV) {

    WavetableOscillator* out = malloc(sizeof(WavetableOscillator));
    out->frequency = frequency;
    out->name = name;
    out->waveTable = waveTable;
    out->wavetableLength = wavetableLength;
    out->sampleRate = sampleRate;
    out->isOutput = isOutput;
    out->index = 0;
    out->isCV = isCV;
    out->sample = 0.0;
    out->volume = 1;
    return out;
}
float getWavetableSample(WavetableOscillator* oscillator) {
    if (oscillator->index >= oscillator->wavetableLength) {
        oscillator->index = 0;
    }
    float out = oscillator->waveTable[oscillator->index];
    float temp = (float)oscillator->frequency / 10;
    int n = (temp - floor(temp) > 0.5) ? ceil(temp) : floor(temp);
    oscillator->index += n;
    oscillator->sample = out;
    //printf("isCV: %d isOutput: %d\n", oscillator->isCV, oscillator->isOutput);
    if (oscillator->isCV == 1) {
        oscillator->sample = oscillator->sample + 1.0;
    }
    if (oscillator->isOutput == 1) {
        return oscillator->sample;
    }
    else {
        return 0.0;
    }
}

float* loadWavetableByName(char* name) {
#ifndef SLANGONIC
    setlocale(LC_NUMERIC, "C");  // <-- das ist der Schlüssel
    char *line = NULL;
    size_t len = 0;
    int i = 0;
    float* out = malloc(sizeof(float) * 4800);

    char path[1024];
    snprintf(path, 1024, "%s/%s.swave", WAVETABLE_FILE_PATH, name);

    FILE *fp = fopen(path, "r");
    if (!fp) { 
        perror("fopen"); 
        return NULL; 
    }

    while (getline(&line, &len, fp) != -1) {
        // BOM entfernen falls vorhanden
        if ((unsigned char)line[0] == 0xEF) line += 3;

        line[strcspn(line, "\r\n")] = '\0';

        char *end;
        errno = 0;
        double val = strtod(line, &end);
        if (end == line) {
            continue;
        }

        out[i++] = (float)val;
    }

    free(line);
    fclose(fp);
    return out;
#endif
}
