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

void parseFunction(SlangInterpreter* si, int* i) {
    consume(i, getToken(si, *i), FUNCTION);
    printDebugMessage(INFO, "Function definition found!");

    char* fnName = NULL;

    if(peek(getToken(si, *i), IDENTIFIER)) {
        printDebugMessage(DBG, "Function name:");
        printDebugMessage(DBG, getToken(si, *i).value);
        fnName = getToken(si, *i).value;
    }
    consume(i, getToken(si, *i), IDENTIFIER);
    consume(i, getToken(si, *i), PARANTHESISLEFT);

    char** var_names = malloc(sizeof(char)*1024);
    int vars_length = 0;

    while(getToken(si, *i).tt != PARANTHESISRIGHT) {
        var_names[vars_length] = getToken(si, *i).value;
        printDebugMessage(INFO, var_names[vars_length]);
        consume(i, getToken(si, *i), IDENTIFIER);
        if(getToken(si, *i).tt != PARANTHESISRIGHT) {
            consume(i, getToken(si, *i), COMMA);
        }
        vars_length++;
    }
    consume(i, getToken(si, *i), PARANTHESISRIGHT);
    consume(i, getToken(si, *i), BRACKETLEFT);

    Token* function_tokens = malloc(sizeof(Token) * 8192);
    int numFunctionTokens = 0;

    while(getToken(si, *i).tt != BRACKETRIGHT) {
        function_tokens[numFunctionTokens] = getToken(si, *i);
        inc(i);
        numFunctionTokens++;
    }

    LOGINFO("Creating function: %s with %d argmuents", fnName, vars_length);

    addFunction(si, createFunction(fnName, function_tokens, numFunctionTokens, var_names, vars_length));
    consume(i, getToken(si, *i), BRACKETRIGHT);
}

void parseExpression(SlangInterpreter* si, int* i) {
    if(getToken(si, (*i)+1).tt == ASSIGN) {
        char* name = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), ASSIGN);
        double value = l3_expression(si, i);

        if(getVariableByName(si, name) != NULL) {
            getVariableByName(si, name)->value = value;
        }
        else {
            Variable* temp_var = malloc(sizeof(Variable));
            temp_var->name = name;
            temp_var->value = value;

            addVariable(si, temp_var);
        }
    }
    else {
        double value = l3_expression(si, i);
        printf("%lf\n", value);
    }
    consume(i, getToken(si, *i), SEMICOLON);
}
