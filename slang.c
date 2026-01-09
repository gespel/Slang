//
// Created by stenh
//
#include "slang-lib.h"
//#define LIBRARY
#ifndef LIBRARY

void printLogo() {
    printf("         _            _             _                   _             _\n");
    printf("        / /\\         _\\ \\          / /\\                /\\ \\     _    /\\ \n");
    printf("       / /  \\       /\\__ \\        / /  \\              /  \\ \\   /\\_\\ /  \\ \n");
    printf("      / / /\\ \\__   / /_ \\_\\      / / /\\ \\            / /\\ \\ \\_/ / // /\\ \\_\n");
    printf("     / / /\\ \\___\\ / / /\\/_/     / / /\\ \\ \\          / / /\\ \\___/ // / /\\/_/\n");
    printf("     \\ \\ \\ \\/___// / /         / / /  \\ \\ \\        / / /  \\/____// / / ______\n");
    printf("      \\ \\ \\     / / /         / / /___/ /\\ \\      / / /    / / // / / /\\_____\n");
    printf("  _    \\ \\ \\   / / / ____    / / /_____/ /\\ \\    / / /    / / // / /  \\/____ /\n");
    printf(" /_/\\__/ / /  / /_/_/ ___/\\ / /_________/\\ \\ \\  / / /    / / // / /_____/ / /\n");
    printf(" \\ \\/___/ /  /_______/\\__\\// / /_       __\\ \\_\\/ / /    / / // / /______\\/ /\n");
    printf("  \\_____\\/   \\_______\\/    \\_\\___\\     /____/_/\\/_/     \\/_/ \\/___________/\n");
    printf("By Sten (gespel) Heimbrodt - www.sten-heimbrodt.de; www.github.com/gespel/Slang\n\n");
}

int main(int argc, char **argv) {
	printLogo();

	int live_render_active = 0;
	char *pTmp;

	if (( pTmp = getenv( "SLANG_LIVE_RENDER" )) != NULL ) {
  		if (pTmp[0] == '1') {
			live_render_active = 1;
		}

	}
	else {
		printf("SLANG_LIVE_RENDER is set to %s. No audio output is printed\n", pTmp);
	}


    if(argc == 2) {
        char p[16384];
        char buff[2048];
        FILE *f = fopen(argv[1], "r");

        while(fgets(buff, 2048, f)) {
            strcat(p, buff);
        }
        //printf("Read programm: %s\n", p);

        int length = 0;
        Token* tokens = tokenize(p, &length);
        //printTokens(tokens, length);

        printf("%d tokens!\n", length);
        SlangInterpreter* main_interpreter = createSlangInterpreter(tokens, length);
        

        SlangBufferCore* sbc = createBufferCore(main_interpreter, 48000, 512);

        interpret(main_interpreter);

        printAllFunctions(main_interpreter);
        printAllVariables(main_interpreter);
        printAllOscillators(main_interpreter);

		while (live_render_active == 1) {
			float* buf = renderBuffer(sbc);
        	printAudioBuffer(buf, 512);
		}


        free(main_interpreter);
    }
    else {
        printf("Wrong number of arguments!\nUsage: slang <file>\n");
    }

    return 0;
}
#endif
