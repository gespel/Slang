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

void printAudioBuffer(double* audioBuffer, int length) {
    for(int j = 0; j < length; j++) {
        if (audioBuffer[j]) {
            printf("\t%d: %lf ", j, audioBuffer[j]);
        }
        if ((j+1) % 8 == 0) {
            printf("\n");
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
    for(int i = 0; i < si->main_rack->numSineOscillators; i++) {
        LOGINFO("SineOscillator %s: %lf Hz and %lf volume-multiplier", si->main_rack->sine_oscillators[i]->name, si->main_rack->sine_oscillators[i]->frequency[0], si->main_rack->sine_oscillators[i]->volume);
    }
    for(int i = 0; i < si->main_rack->numWaveOscillators; i++) {
        LOGINFO("WavetableOscillator %s: %lf Hz and %lf volume-multiplier", si->main_rack->wave_oscillators[i]->name, si->main_rack->wave_oscillators[i]->frequency[0], si->main_rack->wave_oscillators[i]->volume);
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

double noteNameToFrequency(char *name) {
    char *notes[] = {"c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "a#", "b"};
    //a = 1; a# = 1 + 1/12; b = 1 + 2/12; g# = 1 - 1/12; g = 1 - 2/12; f# = 1 - 3/12; f = 1 - 4/12; e = 1 - 5/12; d# = 1 - 6/12; d = 1 - 7/12; c# = 1 - 8/12; c = 1 - 9/12
    double c0 = 16.3516;
    int noteIndex = 0;
    char *noteName = malloc(sizeof(char) * 3);


    if (name[1] == '#') {
        noteName[0] = name[0];
        noteName[1] = name[1];
        noteName[2] = '\0';
        noteIndex = name[2];
    }
    else {
        noteName[0] = name[0];
        noteName[1] = '\0';
        noteIndex = name[1];
    }

    int index = 0;
    for (int i = 0; i < 11; i++) {
        if (strcmp(noteName, notes[i]) == 0) {
            index = i;
        }
    }

    double baseFrequency = c0 * pow(2, index);

    double frequency = baseFrequency * pow(2, noteIndex);

    return frequency;
}