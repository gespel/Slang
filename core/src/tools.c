#include "../include/tools.h"

void printDebugMessage(SlangLogLevel ll, char* message) {
#ifdef SLANG_DEBUG
    char buffer[30];
    struct timeval tv;
    time_t curtime;
    gettimeofday(&tv, NULL); 
    curtime = tv.tv_sec;
    strftime(buffer,30,"%d-%m-%Y %T", localtime(&curtime));

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
            printf("\t%d: %lf ", j, audioBuffer[j]);
            if ((j+1) % 8 == 0) {
                printf("\n");
            }
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
    for(int i = 0; i < si->main_rack->numOscillators; i++) {
        switch (si->main_rack->oscillators[i]->type) {
            case SINE:
                LOGINFO("SineOscillator %s: %lf Hz and %lf volume-multiplier", si->main_rack->oscillators[i]->data->sine->name, si->main_rack->oscillators[i]->data->sine->frequency[0], si->main_rack->oscillators[i]->data->sine->volume);
                break;
            case WAVETABLE:
                LOGINFO("WavetableOscillator %s: %lf Hz and %lf volume-multiplier", si->main_rack->oscillators[i]->data->wavetable->name, si->main_rack->oscillators[i]->data->wavetable->frequency[0], si->main_rack->oscillators[i]->data->wavetable->volume);
                break;
            case SAWTOOTH:
                LOGINFO("SawtoothOscillator %s: %lf Hz and %lf volume-multiplier", si->main_rack->oscillators[i]->data->sawtooth->name, si->main_rack->oscillators[i]->data->sawtooth->frequency[0], si->main_rack->oscillators[i]->data->sawtooth->volume);
                break;
            case SQUARE:
                LOGINFO("SquareOscillator %s: %lf Hz and %lf volume-multiplier", si->main_rack->oscillators[i]->data->square->name, si->main_rack->oscillators[i]->data->square->frequency[0], si->main_rack->oscillators[i]->data->square->volume);
                break;
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