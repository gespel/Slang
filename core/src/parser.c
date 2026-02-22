//
// Created by Sten on 28.06.2025.
//
#include "core/include/parser.h"
#include "core/include/core_types.h"
#include "core/include/interpreter.h"
#include "core/include/tools.h"
#include "core/include/rack.h"
#include "modules/modifier/include/modifier_types.h"
#include "modules/modifier/include/modifier.h"
#include "modules/envelope/include/envelope_types.h"
#include "modules/envelope/include/linenvelope.h"
#include "modules/envelope/include/envelope.h"
#include "modules/sample-source/include/sample_source.h"
#include "modules/oscillators/include/oscillator.h"
#include "modules/oscillators/include/oscillator_types.h"
#include "modules/oscillators/include/random.h"
#include "modules/reverb/include/springreverb.h"
#include "modules/reverb/include/reverb.h"
#include <time.h>

void parseOscillatorSuffixArguments(SlangInterpreter* si, int* i, float* freqptr, int* is_output, int *is_cv) {
    //char* freq_token = getToken(si, *i).value;
    /*if(getSampleSource(si->main_rack, freq_token) != NULL) {
        consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
        LOGINFO("Using token %s as frequency input", freq_token);
        SampleSource *ss = getSampleSource(si->main_rack, freq_token);
        LOGINFO("Found sample source with type %d", ss->type);
        *freqptr = getSampleSourceSample(ss);
        LOGINFO("Using sample source %f as frequency input", *freqptr);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);
    }

    else if (getInputIndex(getToken(si, *i)) != -1) {
        int index = getInputIndex(getToken(si, *i));
        switch(index) {
            case 0:
                consume(i, getToken(si, *i), TOKEN_INPUTA);
                freqptr = si->inputs[0];
                break;
            case 1:
                consume(i, getToken(si, *i), TOKEN_INPUTB);
                freqptr = si->inputs[1];
                break;
            case 2:
                consume(i, getToken(si, *i), TOKEN_INPUTC);
                freqptr = si->inputs[2];
                break;
            case 3:
                consume(i, getToken(si, *i), TOKEN_INPUTD);
                freqptr = si->inputs[3];
                break;
            default:
                break;
        }
        consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);
    }
    else {
        *freqptr = l3_expression(si, i);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);
    }*/
    *freqptr = l3_expression(si, i);
    /*while(getToken(si, *i).tt != TOKEN_PARANTHESISRIGHT) {
        (*i)++;
    }*/
    consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);
    if (getToken(si, *i).tt == TOKEN_MINUS) {
        consume(i, getToken(si, *i), TOKEN_MINUS);
        *is_output = 0;
        *is_cv = 0;
    }
    else if (getToken(si, *i).tt == TOKEN_PLUS) {
        consume(i, getToken(si, *i), TOKEN_PLUS);
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

    if (getToken(si, *i).tt == TOKEN_WAVEOSC) {
        consume(i, getToken(si, *i), TOKEN_WAVEOSC);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);
        int argumentIndex = *i;
        char* waveName = getToken(si, *i).value;
        consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
        consume(i, getToken(si, *i), TOKEN_COMMA);

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

	if (getToken(si, *i).tt == TOKEN_SAWOSC) {
		consume(i, getToken(si, *i), TOKEN_SAWOSC);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);
        int argumentIndex = *i;

        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

        LOGDEBUG("is output %d is cv: %d and init freq: %f", *is_output, *is_cv, freq);
	    SawtoothOscillator *osc = createSawtoothOscillator(freq, name, si->sampleRate, *is_output, *is_cv);

	    Oscillator *o = createOscillator(osc, SAWTOOTH);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a SAWTOOTHOSC with %f Hz and name %s (argument index %d)", osc->frequency, osc->name, argumentIndex);
	}

    if(getToken(si, *i).tt == TOKEN_SINEOSC) {
        consume(i, getToken(si, *i), TOKEN_SINEOSC);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);
        int argumentIndex = *i;
        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

		WavetableOscillator* osc = createWavetableOscillator(freq, name, sine_wave, 4800, si->sampleRate, *is_output, *is_cv);

		Oscillator *o = createOscillator(osc, WAVETABLE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a SINESYNTH with %f Hz and name %s", osc->frequency, osc->name);
    }
    if (getToken(si, *i).tt == TOKEN_TRUESINEOSC) {
        consume(i, getToken(si, *i), TOKEN_TRUESINEOSC);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);

        int argumentIndex = *i;

        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

        SineOscillator *osc = createSineOscillator(freq, name, si->sampleRate, *is_output, *is_cv);

		Oscillator *o = createOscillator(osc, SINE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a SINESYNTH with %f Hz and name %s", osc->frequency, osc->name);
    }
    if (getToken(si, *i).tt == TOKEN_RANDOMOSC) {
        consume(i, getToken(si, *i), TOKEN_RANDOMOSC);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);
        int argumentIndex = -1;

        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

        RandomOscillator *osc = createRandomOscillator(name, *is_output, *is_cv);

        Oscillator *o = createOscillator(osc, RANDOM_OSC_TYPE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);

        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating RANDOMOSC with name %s", osc->name);
    }
    if (getToken(si, *i).tt == TOKEN_TRIANGLEOSC) {
        consume(i, getToken(si, *i), TOKEN_TRIANGLEOSC);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);

        int argumentIndex = *i;

        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

        TriangleOscillator *osc = createTriangleOscillator(freq, name, si->sampleRate, *is_output, *is_cv);

        Oscillator *o = createOscillator(osc, TRIANGLE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
        addSampleSource(si->main_rack, sampleSource);

        LOGINFO("Creating a TRIANGLEOSC with %f Hz and name %s", osc->frequency, osc->name);
    }
    if (getToken(si, *i).tt == TOKEN_SQUAREOSC) {
        consume(i, getToken(si, *i), TOKEN_SQUAREOSC);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);

        int argumentIndex = *i;

        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

        SquareOscillator *osc = createSquareOscillator(freq, name, si->sampleRate, *is_output, *is_cv);

        Oscillator *o = createOscillator(osc, SQUARE);

        SampleSource *sampleSource = createSampleSource(name, o, OSCILLATOR, argumentIndex);
        addSampleSource(si->main_rack, sampleSource);
    }
    if (getToken(si, *i).tt == TOKEN_TERRAINOSC) {
        consume(i, getToken(si, *i), TOKEN_TERRAINOSC);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);
        //char* terrainName = getToken(si, *i).value;
        consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
        consume(i, getToken(si, *i), TOKEN_COMMA);
        parseOscillatorSuffixArguments(si, i, &freq, is_output, is_cv);

        //TODO: implement terrain oscillator creation
    }
}



void parseFunction(SlangInterpreter* si, int* i) {
    consume(i, getToken(si, *i), TOKEN_FUNCTION);
    printDebugMessage(INFO, "Function definition found!");

    char* fnName = NULL;

    if(peek(getToken(si, *i), TOKEN_IDENTIFIER)) {
        printDebugMessage(DBG, "Function name:");
        printDebugMessage(DBG, getToken(si, *i).value);
        fnName = getToken(si, *i).value;
    }
    consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
    consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);

    char** var_names = malloc(sizeof(char)*1024);
    int vars_length = 0;

    while(getToken(si, *i).tt != TOKEN_PARANTHESISRIGHT) {
        var_names[vars_length] = getToken(si, *i).value;
        printDebugMessage(INFO, var_names[vars_length]);
        consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
        if(getToken(si, *i).tt != TOKEN_PARANTHESISRIGHT) {
            consume(i, getToken(si, *i), TOKEN_COMMA);
        }
        vars_length++;
    }
    consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);
    consume(i, getToken(si, *i), TOKEN_BRACKETLEFT);

    Token* function_tokens = malloc(sizeof(Token) * 8192);
    int numFunctionTokens = 0;

    while(getToken(si, *i).tt != TOKEN_BRACKETRIGHT) {
        function_tokens[numFunctionTokens] = getToken(si, *i);
        inc(i);
        numFunctionTokens++;
    }

    LOGINFO("Creating function: %s with %d argmuents", fnName, vars_length);

    addFunction(si, createFunction(fnName, function_tokens, numFunctionTokens, var_names, vars_length));
    consume(i, getToken(si, *i), TOKEN_BRACKETRIGHT);
}

void parseExpression(SlangInterpreter* si, int* i) {
    if(getToken(si, (*i)+1).tt == TOKEN_ASSIGN && isOscillator(getToken(si, (*i)+2)) == 1) {
        char *name = getToken(si, *i).value;
        consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
        consume(i, getToken(si, *i), TOKEN_ASSIGN);

        parseOscillators(si, i, name);
    }
    else if (getToken(si, (*i)+1).tt == TOKEN_ASSIGN && getToken(si, (*i)+2).tt == TOKEN_STEPSEQ) {
        char *name = getToken(si, *i).value;
        consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
        consume(i, getToken(si, *i), TOKEN_ASSIGN);
    
        parseStepSequencer(si, i, name);
    }
    else if (getToken(si, (*i)+1).tt == TOKEN_ASSIGN && getToken(si, (*i)+2).tt == TOKEN_LINENVELOPE) {
        char* name = getToken(si, *i).value;
        consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
        consume(i, getToken(si, *i), TOKEN_ASSIGN);

        parseEnvelopeGenerator(si, i, name);
    }
    else if(getToken(si, (*i)+1).tt == TOKEN_ASSIGN) {
        char* name = getToken(si, *i).value;
        consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
        consume(i, getToken(si, *i), TOKEN_ASSIGN);
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
    consume(i, getToken(si, *i), TOKEN_SEMICOLON);
}

void parseStepSequencer(SlangInterpreter* si, int* i, char* name) {
    consume(i, getToken(si, *i), TOKEN_STEPSEQ);
    consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);
    int argumentIndex = *i;
    float *speed = malloc(sizeof(float));
    float *sequence = malloc(sizeof(float) * 128);
    int sequence_len = 0;

    consume(i, getToken(si, *i), TOKEN_SQUAREBRACKETLEFT);
    while (getToken(si, *i).tt != TOKEN_SQUAREBRACKETRIGHT) {
        float value = atof(getToken(si, *i).value);
        consume(i, getToken(si, *i), TOKEN_NUMBER);
        sequence[sequence_len] = value;
        sequence_len++;

        if (getToken(si, *i).tt == TOKEN_SQUAREBRACKETRIGHT) {
            break;
        }
        consume(i, getToken(si, *i), TOKEN_COMMA);
    }
    consume(i, getToken(si, *i), TOKEN_SQUAREBRACKETRIGHT);
    consume(i, getToken(si, *i), TOKEN_COMMA);

    speed[0] = atof(getToken(si, *i).value);
    consume(i, getToken(si, *i), TOKEN_NUMBER);
    consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);
    StepSequencer *step = createStepSequencer(si->sampleRate, speed[0], sequence, sequence_len);
    SampleSource *sampleSource = createSampleSource(name, step, STEPSEQUENCER, argumentIndex);
    addSampleSource(si->main_rack, sampleSource);


    LOGINFO("Creating a STEPSEQUENCER with speed %f and name %s", speed[0], name);
}

void parseIf(SlangInterpreter* si, int* i) {
    consume(i, getToken(si, *i), TOKEN_IF);
    consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);

    printDebugMessage(DBG, "IF call found! Evaluating now!");

    int l = checkLogic(si, i);

    consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);
    consume(i, getToken(si, *i), TOKEN_BRACKETLEFT);
    int nrbr = si->openBrackets;
    si->openBrackets++;
    if (l == 0) {
        while (si->openBrackets > nrbr) {
            if (getToken(si, *i).tt == TOKEN_BRACKETRIGHT) {
                si->openBrackets--;
            }
            i++;
        }
    }
}

void parseFilter(SlangInterpreter* si, int* i) {
    //int filter_type = -1;
    if(getToken(si, *i).tt == TOKEN_LOWPASSFILTER) {
        consume(i, getToken(si, *i), TOKEN_LOWPASSFILTER);
        //filter_type = 1;
    }
    else if(getToken(si, *i).tt == TOKEN_HIGHPASSFILTER) {
        consume(i, getToken(si, *i), TOKEN_HIGHPASSFILTER);
        //filter_type = 2;
    }
    else {
        LOGERROR("Filter type not recognized!");
    }
    consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);
    
    if(getToken(si, *i).tt == TOKEN_MAIN) {
        consume(i, getToken(si, *i), TOKEN_MAIN);
        consume(i, getToken(si, *i), TOKEN_COMMA);
        int argumentIndex = *i;

        float freq = l3_expression(si, i);

        consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);
        
        LowPassFilter* filter = createLowPassFilter(freq, si->sampleRate);
        Filter *f = malloc(sizeof(Filter));
        f->type = LOWPASSFILTER;
        f->filter = filter;
        f->argumentIndex = argumentIndex;
        addFilter(si->main_rack, f);
        LOGINFO("Creating a LOWPASSFILTER on main bus with cutoff %f", freq);
    }

    
    
    else if (getToken(si, *i).tt == TOKEN_IDENTIFIER) {
        char* name = getToken(si, *i).value;
        consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
        consume(i, getToken(si, *i), TOKEN_COMMA);

        int argumentIndex = *i;
        float freq = l3_expression(si, i);
        consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);


        LowPassFilter *filter = createLowPassFilter(freq, si->sampleRate);
        Filter *f = malloc(sizeof(Filter));
        f->type = LOWPASSFILTER;
        f->filter = filter;
        f->argumentIndex = argumentIndex;
        Modifier *modifier = createModifier(f, FILTER);

        SampleSource *ss = getSampleSource(si->main_rack, name);
        if (ss == NULL) {
            LOGERROR("Unable to find SampleSource %s to add Filter", name);
        }
        addModifierToSampleSource(ss, modifier);

        LOGINFO("Creating a LOWPASSFILTER for the sample source %s with cutoff %f", name, freq);
    }
}

void parseEnvelopeGenerator(SlangInterpreter *si, int *i, char* name) {
    consume(i, getToken(si, *i), TOKEN_LINENVELOPE);
    consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);
    int argumentIndex = *i;
    char* stepSequencerName = getToken(si, *i).value;
    consume(i, getToken(si, *i), TOKEN_IDENTIFIER);
    consume(i, getToken(si, *i), TOKEN_COMMA);
    float attack = l3_expression(si, i);
    consume(i, getToken(si, *i), TOKEN_COMMA);
    float decay = l3_expression(si,  i);
    consume(i, getToken(si, *i), TOKEN_COMMA);
    float sustain = l3_expression(si, i);
    consume(i, getToken(si, *i), TOKEN_COMMA);
    float release = l3_expression(si, i);
    consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);

    LinearEnvelopeGenerator* linearEnvelopeGenerator = createLinearEnvelopeGenerator(name, si->sampleRate, attack, decay, sustain, release);
    EnvelopeGenerator* envelopeGenerator = createEnvelopeGenerator(linearEnvelopeGenerator, LINENVELOPE, getSampleSource(si->main_rack, stepSequencerName)->sampleSource);
    SampleSource* sampleSource = createSampleSource(name, envelopeGenerator, ENVELOPEGENERATOR, argumentIndex);

    addSampleSource(si->main_rack, sampleSource);

    LOGINFO("Adding LINEARENVELOPEGENERATOR to samples sources with name %s!", name);
}

void parseReverb(SlangInterpreter *si, int *i) {
    consume(i, getToken(si, *i), TOKEN_SPRINGREVERB);
    consume(i, getToken(si, *i), TOKEN_PARANTHESISLEFT);
    float size = l3_expression(si, i);
    consume(i, getToken(si, *i), TOKEN_COMMA);
    float feedback = l3_expression(si, i);
    consume(i, getToken(si, *i), TOKEN_COMMA);
    float drywet = l3_expression(si, i);
    consume(i, getToken(si, *i), TOKEN_PARANTHESISRIGHT);

    SpringReverb* spring = createSpringReverb(size, feedback, drywet, si->sampleRate);
    Reverb* reverb = createReverb(spring, SPRINGREVERB);

    addReverb(si->main_rack, reverb);

    LOGINFO("Creating Reverb!");
}