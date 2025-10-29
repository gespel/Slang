//
// Created by Sten on 28.06.2025.
//
#include "../include/parser.h"

void parseOscillatorSuffixArguments(SlangInterpreter* si, int* i, float** freqptr, float* frequency_multiplier, int* is_output, int *is_cv) {
    char* freq_token = getToken(si, *i).value;
    if(getSampleSource(si->main_rack, freq_token) != NULL) {
        consume(i, getToken(si, *i), IDENTIFIER);
        LOGINFO("Using token %s as frequency input", freq_token);
        SampleSource *ss = getSampleSource(si->main_rack, freq_token);
        LOGINFO("Found sample source with type %d", ss->type);
        *freqptr = getSampleSourceSamplePtr(ss);
        LOGINFO("Using sample source %f as frequency input", **freqptr);
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
                *freqptr = si->inputs[0];
                break;
            case 1:
                consume(i, getToken(si, *i), INPUTB);
                *freqptr = si->inputs[1];
                break;
            case 2:
                consume(i, getToken(si, *i), INPUTC);
                *freqptr = si->inputs[2];
                break;
            case 3:
                consume(i, getToken(si, *i), INPUTD);
                *freqptr = si->inputs[3];
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
    else {
        (*freqptr)[0] = l3_expression(si, i);
        consume(i, getToken(si, *i), PARANTHESISRIGHT);
    }
    if (getToken(si, *i).tt == MINUS) {
        consume(i, getToken(si, *i), MINUS);
        *is_output = 0;
        *is_cv = 0;
    }
    else if (getToken(si, *i).tt == PLUS) {
        consume(i, getToken(si, *i), PLUS);
        *is_cv = 1;
        *is_output = 0;
    }
    else {
        *is_output = 1;
        *is_cv = 0;
    }
}

void parseOscillators(SlangInterpreter* si, int* i, char *name) {
    float* freqptr = malloc(sizeof(float));
    float frequency_multiplier = 1.0;
    int* is_output = malloc(sizeof(int));
    int* is_cv = malloc(sizeof(int));
    is_output[0] = 1;

    if (getToken(si, *i).tt == WAVEOSC) {
        consume(i, getToken(si, *i), WAVEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);
        char* waveName = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), COMMA);

        parseOscillatorSuffixArguments(si, i, &freqptr, &frequency_multiplier, is_output, is_cv);

		float *wt = loadWavetableByName(waveName);

		if(wt != NULL) {
			//WavetableOscillator* osc = createWavetableOscillator(freqptr, frequency_multiplier, name, getWavetableByName(waveName), 4800, 48000, *is_output);
		    WavetableOscillator* osc = createWavetableOscillator(freqptr, frequency_multiplier, name, loadWavetableByName(waveName), 4800, si->sampleRate, *is_output, *is_cv);
		    Oscillator *o = createOscillator(osc, WAVETABLE);
            SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR);
            addSampleSource(si->main_rack, sampleSource);

            LOGINFO("Creating a WAVEOSC with %f Hz and name %s", osc->frequency[0], osc->name);
		}
		else {
			LOGERROR("could not find given wavetable %s", waveName);
		}

    }

	if (getToken(si, *i).tt == SAWOSC) {
		consume(i, getToken(si, *i), SAWOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        parseOscillatorSuffixArguments(si, i, &freqptr, &frequency_multiplier, is_output, is_cv);

        printf("is output %d is cv: %d\n", *is_output, *is_cv);
	    SawtoothOscillator *osc = createSawtoothOscillator(freqptr, frequency_multiplier, name, si->sampleRate, *is_output, *is_cv);

	    Oscillator *o = createOscillator(osc, SAWTOOTH);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a SAWTOOTHOSC with %f Hz and name %s", osc->frequency[0], osc->name);
	}

    if(getToken(si, *i).tt == SINEOSC) {
        consume(i, getToken(si, *i), SINEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        parseOscillatorSuffixArguments(si, i, &freqptr, &frequency_multiplier, is_output, is_cv);

		WavetableOscillator* osc = createWavetableOscillator(freqptr, frequency_multiplier, name, sine_wave, 4800, si->sampleRate, *is_output, *is_cv);

		Oscillator *o = createOscillator(osc, WAVETABLE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a SINESYNTH with %f Hz and name %s", osc->frequency[0], osc->name);
    }
    if (getToken(si, *i).tt == TRUESINEOSC) {
        consume(i, getToken(si, *i), TRUESINEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        parseOscillatorSuffixArguments(si, i, &freqptr, &frequency_multiplier, is_output, is_cv);

        SineOscillator *osc = createSineOscillator(freqptr, frequency_multiplier, name, si->sampleRate, *is_output, *is_cv);

		Oscillator *o = createOscillator(osc, SINE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a SINESYNTH with %f Hz and name %s", osc->frequency[0], osc->name);
    }
    if (getToken(si, *i).tt == TRIANGLEOSC) {
        consume(i, getToken(si, *i), TRIANGLEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        parseOscillatorSuffixArguments(si, i, &freqptr, &frequency_multiplier, is_output, is_cv);

        TriangleOscillator *osc = createTriangleOscillator(freqptr, frequency_multiplier, name, si->sampleRate, *is_output, *is_cv);

        Oscillator *o = createOscillator(osc, TRIANGLE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a TRIANGLEOSC with %f Hz and name %s", osc->frequency[0], osc->name);
    }
    if (getToken(si, *i).tt == SQUAREOSC) {
        consume(i, getToken(si, *i), SQUAREOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        parseOscillatorSuffixArguments(si, i, &freqptr, &frequency_multiplier, is_output, is_cv);

        SquareOscillator *osc = createSquareOscillator(freqptr, frequency_multiplier, name, si->sampleRate, *is_output, *is_cv);

        Oscillator *o = createOscillator(osc, SQUARE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR);
        addSampleSource(si->main_rack, sampleSource);
    }
    if (getToken(si, *i).tt == TERRAINOSC) {
        consume(i, getToken(si, *i), TERRAINOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);
        char* terrainName = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), COMMA);
        parseOscillatorSuffixArguments(si, i, &freqptr, &frequency_multiplier, is_output, is_cv);

        //TODO: implement terrain oscillator creation
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
    else if (getToken(si, (*i)+1).tt == ASSIGN && getToken(si, (*i)+2).tt == STEPSEQ) {
        char *name = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), ASSIGN);
    
        parseStepSequencer(si, i, name);
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

void parseStepSequencer(SlangInterpreter* si, int* i, char* name) {
    consume(i, getToken(si, *i), STEPSEQ);
    consume(i, getToken(si, *i), PARANTHESISLEFT);
    float *speed = malloc(sizeof(float));
    float *sequence = malloc(sizeof(float) * 128);
    int sequence_len = 0;

    consume(i, getToken(si, *i), SQUAREBRACKETLEFT);
    while (getToken(si, *i).tt != SQUAREBRACKETRIGHT) {
        float value = atof(getToken(si, *i).value);
        consume(i, getToken(si, *i), NUMBER);
        sequence[sequence_len] = value;
        sequence_len++;

        if (getToken(si, *i).tt == SQUAREBRACKETRIGHT) {
            break;
        }
        consume(i, getToken(si, *i), COMMA);
    }
    consume(i, getToken(si, *i), SQUAREBRACKETRIGHT);
    consume(i, getToken(si, *i), COMMA);

    speed[0] = atof(getToken(si, *i).value);
    consume(i, getToken(si, *i), NUMBER);
    consume(i, getToken(si, *i), PARANTHESISRIGHT);
    StepSequencer *step = createStepSequencer(si->sampleRate, speed[0], sequence, sequence_len);
    SampleSource *sampleSource = createSampleSource(name, step, STEPSEQUENCER);
    addSampleSource(si->main_rack, sampleSource);


    LOGINFO("Creating a STEPSEQUENCER with speed %f and name %s", speed[0], name);
}

void parseIf(SlangInterpreter* si, int* i) {
    consume(i, getToken(si, *i), IF);
    consume(i, getToken(si, *i), PARANTHESISLEFT);

    printDebugMessage(DBG, "IF call found! Evaluating now!");

    int l = checkLogic(si, i);

    consume(i, getToken(si, *i), PARANTHESISRIGHT);
    consume(i, getToken(si, *i), BRACKETLEFT);
    int nrbr = si->openBrackets;
    si->openBrackets++;
    if (l == 0) {
        while (si->openBrackets > nrbr) {
            if (getToken(si, *i).tt == BRACKETRIGHT) {
                si->openBrackets--;
            }
            i++;
        }
    }
}

void parseFilter(SlangInterpreter* si, int* i) {
    int filter_type = -1;
    if(getToken(si, *i).tt == LOWPASSFILTERTOKEN) {
        consume(i, getToken(si, *i), LOWPASSFILTERTOKEN);
        filter_type = 1;
    }
    else if(getToken(si, *i).tt == HIGHPASSFILTERTOKEN) {
        consume(i, getToken(si, *i), HIGHPASSFILTERTOKEN);
        filter_type = 2;
    }
    else {
        LOGERROR("Filter type not recognized!");
    }
    consume(i, getToken(si, *i), PARANTHESISLEFT);
    if (getToken(si, i).tt == NUMBER) {
        float *cutoff = malloc(sizeof(float));
        cutoff[0] = l3_expression(si, i);
        consume(i, getToken(si, *i), PARANTHESISRIGHT);
        LowPassFilter* filter = createLowPassFilter(cutoff[0], si->sampleRate);
        Filter *f = malloc(sizeof(Filter));
        f->type = LOWPASSFILTER;
        f->filter = filter;
        addFilter(si->main_rack, f);
        LOGINFO("Creating a LOWPASSFILTER with cutoff %f", cutoff[0]);
    }
    else if (getToken(si, i).tt == IDENTIFIER) {
        char* name = getToken(si, i).value;
        
    }

    
}