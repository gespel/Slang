//
// Created by Sten on 13.07.2025.
//
#include "../include/wavetable.h"

WavetableOscillator* createWavetableOscillator(
    float* frequency,
    float frequencyMultiplier,
    char* name,
    float* waveTable,
    int wavetableLength,
    int sampleRate,
    int isOutput,
    int isCV) {

    WavetableOscillator* out = malloc(sizeof(WavetableOscillator));
    out->frequency = frequency;
    out->frequencyMultiplier = frequencyMultiplier;
    out->name = name;
    out->waveTable = waveTable;
    out->wavetableLength = wavetableLength;
    out->sampleRate = sampleRate;
    out->isOutput = isOutput;
    out->index = 0;
    out->isCV = isCV;
    out->sample = malloc(sizeof(float));
    return out;
}
float getWavetableSample(WavetableOscillator* oscillator) {
    if (oscillator->index >= oscillator->wavetableLength) {
        oscillator->index = 0;
    }
    float out = oscillator->waveTable[oscillator->index];
    float temp = (float)oscillator->frequency[0] / 10;
    int n = (temp - floor(temp) > 0.5) ? ceil(temp) : floor(temp);
    oscillator->index += n;
    oscillator->sample[0] = out;
    if (oscillator->isCV == 1) {
        oscillator->sample[0] = oscillator->sample[0] + 1.0;
    }
    if (oscillator->isOutput == 1) {
        return oscillator->sample[0];
    }
    else {
        return 0.0;
    }
}

float* getWavetableByName(char* name) {
    if (strcmp("strangeone", name) == 0) {
        return random_wave_one;
    }
    if (strcmp("strangetwo", name) == 0) {
        return random_wave_two;
    }
    if (strcmp("strangethree", name) == 0) {
        return random_wave_three;
    }
    if (strcmp("strangefour", name) == 0) {
        return random_wave_four;
    }
    if (strcmp("sine", name) == 0) {
        return sine_wave;
    }

    return NULL;
}

float* loadWavetableByName(char* name) {
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
        //printf("Parsed value: %f\n", out[i-1]);
    }

    free(line);
    fclose(fp);
    return out;
}
