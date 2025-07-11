//
// Created by Sten on 09.06.2025.
//
#include "../include/oscillator.h"

#include <stdio.h>

double getSineSample(SineOscillator* oscillator) {
    oscillator->phase += (oscillator->frequency[0] * oscillator->frequencyMultiplier / oscillator->sampleRate) * 2.0 * M_PI;
    oscillator->sample[0] = sin(oscillator->phase);
    if (oscillator->isOutput == 1) {
        return oscillator->sample[0];
    }
    else {
        return 0.0;
    }
}

double getWavetableSample(WavetableOscillator* oscillator) {
    if (oscillator->index >= oscillator->wavetableLength) {
        oscillator->index = 0;
    }
    double out = oscillator->waveTable[oscillator->index];
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

double getSawtoothSample(SawtoothOscillator* oscillator) {
	if (oscillator->sample[0] >= 1) {
		oscillator->sample[0] = -1.0;
	}
	oscillator->sample[0] = oscillator->sample[0] + (oscillator->frequency[0] / oscillator->sampleRate);
	return oscillator->sample[0];
}

double getSquareSample(SquareOscillator* oscillator) {

}