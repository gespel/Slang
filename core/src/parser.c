//
// Created by Sten on 28.06.2025.
//
#include "core/include/parser.h"
#include "core/include/core_types.h"
#include "core/include/interpreter.h"
#include "core/include/tools.h"
#include "core/include/rack.h"
#include "modules/envelope/include/envelope_types.h"
#include "modules/envelope/include/linenvelope.h"
#include "modules/envelope/include/envelope.h"
#include "modules/sample-source/include/sample_source.h"

void parseOscillatorSuffixArguments(SlangInterpreter* si, int* i, float* freqptr, int* is_output, int *is_cv) {
    //char* freq_token = getToken(si, *i).value;
    /*if(getSampleSource(si->main_rack, freq_token) != NULL) {
        consume(i, getToken(si, *i), IDENTIFIER);
        LOGINFO("Using token %s as frequency input", freq_token);
        SampleSource *ss = getSampleSource(si->main_rack, freq_token);
        LOGINFO("Found sample source with type %d", ss->type);
        *freqptr = getSampleSourceSample(ss);
        LOGINFO("Using sample source %f as frequency input", *freqptr);
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
        consume(i, getToken(si, *i), PARANTHESISRIGHT);
    }
    else {
        *freqptr = l3_expression(si, i);
        consume(i, getToken(si, *i), PARANTHESISRIGHT);
    }*/
    *freqptr = l3_expression(si, i);
    /*while(getToken(si, *i).tt != PARANTHESISRIGHT) {
        (*i)++;
    }*/
    consume(i, getToken(si, *i), PARANTHESISRIGHT);
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
    float freq = 0;
    int* is_output = malloc(sizeof(int));
    int* is_cv = malloc(sizeof(int));
    is_output[0] = 1;

    if (getToken(si, *i).tt == WAVEOSC) {
        consume(i, getToken(si, *i), WAVEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);
        int argumentIndex = *i;
        char* waveName = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), COMMA);

        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

		float *wt = loadWavetableByName(waveName);

		if(wt != NULL) {
		    WavetableOscillator* osc = createWavetableOscillator(freq, name, loadWavetableByName(waveName), 4800, si->sampleRate, *is_output, *is_cv);
		    Oscillator *o = createOscillator(osc, WAVETABLE);
            SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
            addSampleSource(si->main_rack, sampleSource);

            LOGINFO("Creating a WAVEOSC with %f Hz and name %s", osc->frequency, osc->name);
		}
		else {
			LOGERROR("could not find given wavetable %s", waveName);
		}

    }

	if (getToken(si, *i).tt == SAWOSC) {
		consume(i, getToken(si, *i), SAWOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);
        int argumentIndex = *i;

        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

        LOGDEBUG("is output %d is cv: %d and init freq: %f", *is_output, *is_cv, freq);
	    SawtoothOscillator *osc = createSawtoothOscillator(freq, name, si->sampleRate, *is_output, *is_cv);

	    Oscillator *o = createOscillator(osc, SAWTOOTH);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a SAWTOOTHOSC with %f Hz and name %s (argument index %d)", osc->frequency, osc->name, argumentIndex);
	}

    if(getToken(si, *i).tt == SINEOSC) {
        consume(i, getToken(si, *i), SINEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);
        int argumentIndex = *i;
        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

		WavetableOscillator* osc = createWavetableOscillator(freq, name, sine_wave, 4800, si->sampleRate, *is_output, *is_cv);

		Oscillator *o = createOscillator(osc, WAVETABLE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a SINESYNTH with %f Hz and name %s", osc->frequency, osc->name);
    }
    if (getToken(si, *i).tt == TRUESINEOSC) {
        consume(i, getToken(si, *i), TRUESINEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        int argumentIndex = *i;

        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

        SineOscillator *osc = createSineOscillator(freq, name, si->sampleRate, *is_output, *is_cv);

		Oscillator *o = createOscillator(osc, SINE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a SINESYNTH with %f Hz and name %s", osc->frequency, osc->name);
    }
    if (getToken(si, *i).tt == TRIANGLEOSC) {
        consume(i, getToken(si, *i), TRIANGLEOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        int argumentIndex = *i;

        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

        TriangleOscillator *osc = createTriangleOscillator(freq, name, si->sampleRate, *is_output, *is_cv);

        Oscillator *o = createOscillator(osc, TRIANGLE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a TRIANGLEOSC with %f Hz and name %s", osc->frequency, osc->name);
    }
    if (getToken(si, *i).tt == SQUAREOSC) {
        consume(i, getToken(si, *i), SQUAREOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);

        int argumentIndex = *i;

        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

        SquareOscillator *osc = createSquareOscillator(freq, name, si->sampleRate, *is_output, *is_cv);

        Oscillator *o = createOscillator(osc, SQUARE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
        addSampleSource(si->main_rack, sampleSource);
    }
    if (getToken(si, *i).tt == TERRAINOSC) {
        consume(i, getToken(si, *i), TERRAINOSC);
        consume(i, getToken(si, *i), PARANTHESISLEFT);
        //char* terrainName = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), COMMA);
        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

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
    else if (getToken(si, (*i)+1).tt == ASSIGN && getToken(si, (*i)+2).tt == LINENVELOPEGENERATORTOKEN) {
        char* name = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), ASSIGN);

        parseEnvelopeGenerator(si, i, name);
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
    int argumentIndex = *i;
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
    SampleSource *sampleSource = createSampleSource(name, step, STEPSEQUENCER, argumentIndex);
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
    //int filter_type = -1;
    if(getToken(si, *i).tt == LOWPASSFILTERTOKEN) {
        consume(i, getToken(si, *i), LOWPASSFILTERTOKEN);
        //filter_type = 1;
    }
    else if(getToken(si, *i).tt == HIGHPASSFILTERTOKEN) {
        consume(i, getToken(si, *i), HIGHPASSFILTERTOKEN);
        //filter_type = 2;
    }
    else {
        LOGERROR("Filter type not recognized!");
    }
    consume(i, getToken(si, *i), PARANTHESISLEFT);

    int argumentIndex = *i;

    float freq = l3_expression(si, i);

    consume(i, getToken(si, *i), PARANTHESISRIGHT);
    
    LowPassFilter* filter = createLowPassFilter(freq, si->sampleRate);
    Filter *f = malloc(sizeof(Filter));
    f->type = LOWPASSFILTER;
    f->filter = filter;
    f->argumentIndex = argumentIndex;
    addFilter(si->main_rack, f);
    LOGINFO("Creating a LOWPASSFILTER on main bus with cutoff %f", freq);
    
    /*else if (getToken(si, *i).tt == IDENTIFIER) {
        char* name = getToken(si, *i).value;
        consume(i, getToken(si, *i), IDENTIFIER);
        consume(i, getToken(si, *i), COMMA);
        float *cutoff = malloc(sizeof(float));
        cutoff[0] = l3_expression(si, i);
        consume(i, getToken(si, *i), PARANTHESISRIGHT);


        LowPassFilter *filter = createLowPassFilter(cutoff, si->sampleRate);
        Filter *f = malloc(sizeof(Filter));
        f->type = LOWPASSFILTER;
        f->filter = filter;
        Modifier *modifier = malloc(sizeof(Modifier));
        modifier->type = FILTER;
        modifier->modifier = f;
        addModifierToSampleSource(si->main_rack, name, modifier);
        LOGINFO("Creating a LOWPASSFILTER for the sample source %s with cutoff %f", name, *cutoff);
    }*/
}

void parseEnvelopeGenerator(SlangInterpreter *si, int *i, char* name) {
    consume(i, getToken(si, *i), LINENVELOPEGENERATORTOKEN);
    consume(i, getToken(si, *i), PARANTHESISLEFT);
    int argumentIndex = *i;
    char* stepSequencerName = getToken(si, *i).value;
    consume(i, getToken(si, *i), IDENTIFIER);
    consume(i, getToken(si, *i), COMMA);
    float attack = l3_expression(si, i);
    consume(i, getToken(si, *i), COMMA);
    float decay = l3_expression(si,  i);
    consume(i, getToken(si, *i), COMMA);
    float sustain = l3_expression(si, i);
    consume(i, getToken(si, *i), COMMA);
    float release = l3_expression(si, i);
    consume(i, getToken(si, *i), PARANTHESISRIGHT);

    LinearEnvelopeGenerator* linearEnvelopeGenerator = createLinearEnvelopeGenerator(name, si->sampleRate, attack, decay, sustain, release);
    EnvelopeGenerator* envelopeGenerator = createEnvelopeGenerator(linearEnvelopeGenerator, LINENVELOPE, getSampleSource(si->main_rack, stepSequencerName)->sampleSource);
    SampleSource* sampleSource = createSampleSource(name, envelopeGenerator, ENVELOPEGENERATOR, argumentIndex);

    addSampleSource(si->main_rack, sampleSource);

    LOGINFO("Adding LINEARENVELOPEGENERATOR to samples sources with name %s!", name);
}