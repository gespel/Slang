#include "core/include/tools.h"
#include "modules/oscillators/include/oscillator_types.h"

void printDebugMessage(SlangLogLevel ll, char* message) {
    char buffer[30];
    struct timeval tv;
    time_t curtime;
    gettimeofday(&tv, NULL);
    curtime = tv.tv_sec;
    strftime(buffer,30,"%d-%m-%Y %T", localtime(&curtime));

    if (ll == ERR) {
        printf("[Slang] \033[34m%s\033[0m - \033[91mERROR\033[0m: %s\n", buffer, message);
        return;
    }
#ifdef SLANG_DEBUG
    char* prefix = malloc(sizeof(char)*16);
    switch (ll) {
        case DBG: prefix = "\033[95mDEBUG\033[0m"; break;
        case INFO: prefix = "\033[92mINFO\033[0m"; break;
        case WARN: prefix = "\033[93mWARNING\033[0m"; break;
        case ERR: prefix = "\033[91mERROR\033[0m"; break;
    }

    printf("[Slang] \033[34m%s\033[0m - %s: %s\n", buffer, prefix, message);
#endif
}

void printTokens(Token* tokens, int length) {
    for(int j = 0; j < length; j++) {
        printf("%s with value %s\n", tokenTypeToString(tokens[j].tt), tokens[j].value);
    }
}

void printAudioBuffer(float* audioBuffer, int length) {
    for(int j = 0; j < length; j++) {
        if (audioBuffer[j]) {
            printf("%lf\n", audioBuffer[j]);
            //printf("\t%d: %lf ", j, audioBuffer[j]);
            //if ((j+1) % 8 == 0) {
            //    printf("\n");
            ///}
        }

    }
}


Token getToken(SlangInterpreter* si, int i) {
    return si->tokens[i];
}

void tokenError(TokenType expected, TokenType got) {
    printf("Unexpected token! Expected '%s' but got '%s'\n", tokenTypeToString(expected), tokenTypeToString(got));
    exit(1);
}

void generalError(char* msg) {
    printf("[ERROR] %s", msg);
    exit(1);
}

void printAllVariables(SlangInterpreter* si) {
#ifdef SLANG_DEBUG
    LOGINFO("=======================================================");
    LOGINFO("Variables:");
    for(size_t i = 0; i < si->vars_length; i++) {
        LOGINFO("%s: %lf", si->variables[i]->name, si->variables[i]->value);
    }
    LOGINFO("=======================================================");
#endif
}

void printAllOscillators(SlangInterpreter* si) {
#ifdef SLANG_DEBUG
    LOGINFO("=======================================================");
    LOGINFO("Oscillators:");
    for(int i = 0; i < si->main_rack->numSampleSources; i++) {
        if (si->main_rack->sampleSources[i]->type != OSCILLATOR) {
            continue;
        }
        if (si->main_rack->sampleSources[i]->type == OSCILLATOR) {
            Oscillator *o = (Oscillator*) si->main_rack->sampleSources[i]->sampleSource;
            switch (o->type) {
                case SINE:
                    LOGINFO("\033[95mSineOscillator\033[0m %s", o->data->sine->name);
                    break;
                case WAVETABLE:
                    LOGINFO("\033[95mWavetableOscillator\033[0m %s", o->data->wavetable->name);
                    break;
                case SAWTOOTH:
                    LOGINFO("\033[95mSawtoothOscillator\033[0m %s", o->data->sawtooth->name);
                    break;
                case SQUARE:
                    LOGINFO("\033[95mSquareOscillator\033[0m %s", o->data->square->name);
                    break;
                case TRIANGLE:
                    LOGINFO("\033[95mTriangleOscillator\033[0m %s", o->data->triangle->name);
                    break;
                case TERRAIN:
                    break;
            }
        }
        

    }
    LOGINFO("=======================================================");
#endif
}

void printAllFunctions(SlangInterpreter* si) {
#ifdef SLANG_DEBUG
    LOGINFO("=======================================================");
    LOGINFO("Functions:");
    for(size_t i = 0; i < si->functions_length; i++) {
        LOGINFO("functionname: %s", si->functions[i]->name);
        for(size_t j = 0; j < si->functions[i]->function_tokens_length; j++) {
            LOGDEBUG("%s -> %s", tokenTypeToString(si->functions[i]->function_tokens[j].tt), si->functions[i]->function_tokens[j].value);
        }
    }
    LOGINFO("=======================================================");
#endif
}

float noteNameToFrequency(char *name) {
    char *notes[] = {"c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "a#", "b"};
    float c0 = 16.3516;
    int noteIndex = 0;
    char *noteName = malloc(sizeof(char) * 3);


    if (name[1] == '#') {
        noteName[0] = name[0];
        noteName[1] = name[1];
        noteName[2] = '\0';
        noteIndex = name[2] - '0';
    }
    else {
        noteName[0] = name[0];
        noteName[1] = '\0';
        noteIndex = name[1] - '0';
    }

    int index = 0;
    for (int i = 0; i < 12; i++) {
        if (strcmp(noteName, notes[i]) == 0) {
            index = i;
        }
    }

    float baseFrequency = c0 * pow(2, (float)index/12);

    float frequency = baseFrequency * pow(2, noteIndex);
	free(noteName);
    return frequency;
}

float randomFloat(float min, float max) {
    srand((unsigned) time(NULL));
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);      /* [min, max] */
}

int randomInt(int min, int max) {
    srand((unsigned) time(NULL));
    return min + rand() % (max - min + 1);
}