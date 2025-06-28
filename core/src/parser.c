//
// Created by Sten on 28.06.2025.
//
#include "../include/parser.h"

void parseOscillators(SlangInterpreter* si, int* i) {
    if(getToken(si, *i).tt == SINEOSC) {
        consume(i, getToken(si, *i), SINEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);
        char* name = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), COMMA);

        double frequency_multiplier = 1.f;
        double* freqptr;
        char* temp = getToken(si, *i).value;
        if(getSineOscillator(si->main_rack, temp) != NULL) {
            SineOscillator* osc = getSineOscillator(si->main_rack, temp);
            freqptr = osc->sample;
            consume(i, getToken(si, *i), IDENTIFIER);
            if(getToken(si, *i).tt == MULTIPLY) {
                consume(i, getToken(si, *i), MULTIPLY);
                frequency_multiplier = l3_expression(si, i);
            }
            consume(i, getToken(si, *i), PARANTHESISRIGHT);
        }
        else {
            double* freq = malloc(sizeof(double));
            freq[0] = l3_expression(si, i);
            freqptr = freq;
            consume(i, getToken(si, *i), PARANTHESISRIGHT);
        }
        //TODO: Move to truesine!
        /*SineOscillator* newOsc = malloc(sizeof(SineOscillator));

        newOsc->sample = malloc(sizeof(double));
        newOsc->name = name;
        newOsc->frequency = freqptr;
        newOsc->frequencyMultiplier = frequency_multiplier;
        newOsc->phase = 0.f;
        newOsc->sampleRate = 0;

        addSineOscillator(si->main_rack, newOsc);*/
        WavetableOscillator* osc = malloc(sizeof(WavetableOscillator));

        osc->sample = malloc(sizeof(double));
        osc->name = name;
        osc->sample = freqptr;
        osc->frequencyMultiplier = frequency_multiplier;
        osc->index = 0;
        osc->frequency = freqptr;
        osc->sampleRate = 0;
        osc->waveTable = sine_wave;
        osc->wavetableLength = 4800;
        addWavetableOscillator(si->main_rack, osc);

        LOGINFO("Creating a SINESYNTH with %lf Hz and name %s", osc->frequency[0], osc->name);
        consume(i, getToken(si, *i), SEMICOLON);
    }
}
