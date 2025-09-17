//
// Created by Sten on 28.06.2025.
//
#include "../include/parser.h"

void parseOscillatorSuffixArguments(SlangInterpreter* si, int* i, float* freqptr, float* frequency_multiplier, int* is_output) {
    char* temp = getToken(si, *i).value;
    if(getOscillator(si->main_rack, temp) != NULL) {
        SineOscillator* osc = getOscillator(si->main_rack, temp);
        freqptr = osc->sample;
        consume(i, getToken(si, *i), IDENTIFIER);
        if(getToken(si, *i).tt == MULTIPLY) {
            consume(i, getToken(si, *i), MULTIPLY);
            frequency_multiplier[0] = l3_expression(si, i);
        }

        consume(i, getToken(si, *i), PARANTHESISRIGHT);
    }
    else if (getInputIndex(getToken(si, *i)) != -1) {
        int index = getInputIndex(getToken(si, *i));
        switch(index) {
            case 0:
                consume(i, getToken(si, *i), INPUTA);
                freqptr = si->inputs[0];
                break;
            case 1:
                consume(i, getToken(si, *i), INPUTB);
                freqptr = si->inputs[1];
                break;
            case 2:
                consume(i, getToken(si, *i), INPUTC);
                freqptr = si->inputs[2];
                break;
            case 3:
                consume(i, getToken(si, *i), INPUTD);
                freqptr = si->inputs[3];
                break;
            default:
                break;
        }
        if(getToken(si, *i).tt == MULTIPLY) {
            consume(i, getToken(si, *i), MULTIPLY);
            frequency_multiplier[0] = l3_expression(si, i);
        }
        consume(i, getToken(si, *i), PARANTHESISRIGHT);
    }
    else if (getSampleSource(si->main_rack, temp) != NULL) {

    }
    else {
        freqptr[0] = l3_expression(si, i);
        consume(i, getToken(si, *i), PARANTHESISRIGHT);
    }
    if (getToken(si, *i).tt == MINUS) {
        consume(i, getToken(si, *i), MINUS);
        *is_output = 0;
    }
    else {
        *is_output = 1;
    }
}

void parseOscillators(SlangInterpreter* si, int* i, char *name) {
    float* freqptr = malloc(sizeof(float*));
    float frequency_multiplier = 1.0;
    int* is_output = malloc(sizeof(int*));
    is_output[0] = 1;

    if (getToken(si, *i).tt == WAVEOSC) {
        consume(i, getToken(si, *i), WAVEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);
        char* waveName = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), COMMA);

        parseOscillatorSuffixArguments(si, i, freqptr, &frequency_multiplier, is_output);

		float *wt = loadWavetableByName(waveName);

		if(wt != NULL) {
			//WavetableOscillator* osc = createWavetableOscillator(freqptr, frequency_multiplier, name, getWavetableByName(waveName), 4800, 48000, *is_output);
		    WavetableOscillator* osc = createWavetableOscillator(freqptr, frequency_multiplier, name, loadWavetableByName(waveName), 4800, si->sampleRate, *is_output);
		    Oscillator *o = createOscillator(osc, WAVETABLE);
		    addOscillator(si->main_rack, o);
            SampleSource *sasou = createSampleSource(o, OSCILLATOR);
		}
		else {
			LOGERROR("could not find given wavetable %s", waveName);
		}

    }

	if (getToken(si, *i).tt == SAWOSC) {
		consume(i, getToken(si, *i), SAWOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        parseOscillatorSuffixArguments(si, i, freqptr, &frequency_multiplier, is_output);

	    SawtoothOscillator *osc = createSawtoothOscillator(freqptr, frequency_multiplier, name, si->sampleRate, *is_output);

	    Oscillator *o = createOscillator(osc, SAWTOOTH);

	    addOscillator(si->main_rack, o);

        LOGINFO("Creating a SAWTOOTHOSC with %lf Hz and name %s", osc->frequency[0], osc->name);
	}

    if(getToken(si, *i).tt == SINEOSC) {
        consume(i, getToken(si, *i), SINEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        parseOscillatorSuffixArguments(si, i, freqptr, &frequency_multiplier, is_output);

		WavetableOscillator* osc = createWavetableOscillator(freqptr, frequency_multiplier, name, sine_wave, 4800, si->sampleRate, *is_output);

		Oscillator *o = createOscillator(osc, WAVETABLE);

        addOscillator(si->main_rack, o);

        LOGINFO("Creating a SINESYNTH with %lf Hz and name %s", osc->frequency[0], osc->name);
    }
    if (getToken(si, *i).tt == TRUESINEOSC) {
        consume(i, getToken(si, *i), TRUESINEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        parseOscillatorSuffixArguments(si, i, freqptr, &frequency_multiplier, is_output);

        SineOscillator *osc = createSineOscillator(freqptr, frequency_multiplier, name, si->sampleRate, *is_output);

		Oscillator *o = createOscillator(osc, SINE);

        addOscillator(si->main_rack, o);

        LOGINFO("Creating a SINESYNTH with %lf Hz and name %s", osc->frequency[0], osc->name);
    }
    if (getToken(si, *i).tt == SQUAREOSC) {
        consume(i, getToken(si, *i), SQUAREOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        parseOscillatorSuffixArguments(si, i, freqptr, &frequency_multiplier, is_output);

        SquareOscillator *osc = createSquareOscillator(freqptr, frequency_multiplier, name, si->sampleRate, *is_output);

        Oscillator *o = createOscillator(osc, SQUARE);

        addOscillator(si->main_rack, o);
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
    if(getToken(si, (*i)+1).tt == ASSIGN && isOscillator(getToken(si, (*i)+2)) == 1) {
        char *name = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), ASSIGN);

        parseOscillators(si, i, name);
    }
    else if(getToken(si, (*i)+1).tt == ASSIGN) {
        char* name = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), ASSIGN);
        float value = l3_expression(si, i);

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
        float value = l3_expression(si, i);
        printf("%lf\n", value);
    }
    consume(i, getToken(si, *i), SEMICOLON);
}
