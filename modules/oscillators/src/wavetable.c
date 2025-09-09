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
    int isOutput) {

    WavetableOscillator* out = malloc(sizeof(WavetableOscillator));
    out->frequency = frequency;
    out->frequencyMultiplier = frequencyMultiplier;
    out->name = name;
    out->waveTable = waveTable;
    out->wavetableLength = wavetableLength;
    out->sampleRate = sampleRate;
    out->isOutput = isOutput;
    out->index = 0;
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
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    float* out = malloc(sizeof(float) * 4800);

    char *path = malloc(sizeof(char) * 1024);
    snprintf(path, 1024, "%s/%s.swave", WAVETABLE_FILE_PATH, name);

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", path);
        exit(1);
    }
    while (getline(&line, &len, fp) != -1) {
        //printf("Read line: %s\n", line);
        out[i] = atof(line);
        LOGINFO("Parsing wavetable value: %f", out[i]);
        //printf("Parsed number: %lf\n", out[0]);
        i++;
    }
    free(path);
    return out;
}