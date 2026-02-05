#include <ctype.h>
#include <string.h>
#include "core/include/tokenizer.h"
#include "core/include/core_types.h"

//
// Created by sten on 11.06.24.
//

Token* tokenize(char* input, int* length) {
    char *cleaned = calloc(strlen(input) + 1, sizeof(char));
    int cleanedLength = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '/' && input[i+1] == '/') {
            while (input[i] != '\n' && i < strlen(input)) {
                i++;
            }
        }
        else {
            cleaned[cleanedLength] = input[i];
            cleanedLength++;
        }
    }
    cleaned[cleanedLength] = '\0';

	Token* out = calloc(1024, sizeof(Token));
	char* tokenString;
  	int tokenCount = 0;
  	tokenString = strtok(cleaned, " \n\t\r");
    int exit_marked = 0;
  	while(tokenString != NULL && exit_marked == 0) {
        for(size_t j = 0; j < strlen(tokenString); j++) {
            if (tokenString[j] == '\0') {
                //printf("EXIT MARK HIT!\n");
                exit_marked = 1;
                break;
            }
            Token temp;
            char *tmpString = malloc(sizeof(char) * 2);

            //printf("lexing char: %c\n", tokenString[j]);
            if(isalpha((unsigned char)tokenString[j])) {
                char* ns = calloc(128, sizeof(char));
                int nsc = 0;
                while(isalpha((unsigned char)tokenString[j]) || isdigit((unsigned char)tokenString[j]) || tokenString[j] == '#') {
                    ns[nsc] = tokenString[j];
                    j++;
                    nsc++;
                }
                j--;

                temp.tt = IDENTIFIER_TOKEN_T;
                temp.value = ns;
                //printf("Tokenzier registered identifier: %s\n", ns);
            }
            else if(tokenString[j] == ';') {
                temp.tt = SEMICOLON_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '=') {
                temp.tt = ASSIGN_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '(') {
                //printf("Opening PARANTHESISLEFT found!\n");
                temp.tt = PARANTHESISLEFT_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == ')') {
                temp.tt = PARANTHESISRIGHT_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '{') {
                temp.tt = BRACKETLEFT_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '}') {
                temp.tt = BRACKETRIGHT_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '[') {
                temp.tt = SQUAREBRACKETLEFT_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == ']') {
                temp.tt = SQUAREBRACKETRIGHT_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '+') {
                temp.tt = PLUS_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '-') {
                temp.tt = MINUS_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '*') {
                temp.tt = MULTIPLY_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '/') {
                temp.tt = DIVIDE_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;

            }
            else if(tokenString[j] == '>') {
                temp.tt = GREATER_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '<') {
                temp.tt = SMALLER_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == ',') {
                temp.tt = COMMA_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if (tokenString[j] == '$') {
                temp.tt = NOTEMARKER_TOKEN_T;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(isdigit((unsigned char)tokenString[j])) {
                //printf("DIGIT found! %c\n", tokenString[j]);
                char* ns = calloc(128, sizeof(char));
                int nsc = 0;
                while(isdigit((unsigned char)tokenString[j]) || tokenString[j] == '.') {
                    //printf("%c is a digit or decimal separator\n", tokenString[j]);
                    ns[nsc] = tokenString[j];
                    j++;
                    nsc++;
                }
                j--;

                temp.tt = NUMBER_TOKEN_T;
                temp.value = ns;
                //printf("Parsed number: %s\n", ns);
            }
            out[tokenCount] = temp;
            tokenCount++;
        }
        tokenString = strtok(NULL, " \n\t\r");
    }

    tokenizeStrings(out, tokenCount);

    *length = tokenCount;
    
    return out;
}

void tokenizeStrings(Token* out, int numTokens) {
    for(int x = 0; x < numTokens; x++) {
        if(out[x].tt == IDENTIFIER_TOKEN_T) {
            char* value = out[x].value;
            if(strcmp(value, "fn") == 0) {
                out[x].tt = FUNCTION_TOKEN_T;
            }
            else if(strcmp(value, "for") == 0) {
                out[x].tt = FOR_TOKEN_T;
            }
            else if(strcmp(value, "if") == 0) {
                out[x].tt = IF_TOKEN_T;
            }
            else if(strcmp(value, "return") == 0) {
                out[x].tt = RETURN_TOKEN_T;
            }
            else if(strcmp(value, "while") == 0) {
                out[x].tt = WHILE_TOKEN_T;
            }
            else if(strcmp(value, "sineosc") == 0) {
                out[x].tt = SINEOSC_TOKEN_T;
            }
            else if(strcmp(value, "sawtoothosc") == 0) {
                out[x].tt = SAWOSC_TOKEN_T;
            }
            else if(strcmp(value, "wavetableosc") == 0) {
                out[x].tt = WAVEOSC_TOKEN_T;
            }
			else if(strcmp(value, "truesineosc") == 0) {
				out[x].tt = TRUESINEOSC_TOKEN_T;
			}
            else if (strcmp(value, "squareosc") == 0) {
                out[x].tt = SQUAREOSC_TOKEN_T;
            }
            else if (strcmp(value, "triangleosc") == 0) {
                out[x].tt = TRIANGLEOSC_TOKEN_T;
            }
            else if (strcmp(value, "randomosc") == 0) {
                out[x].tt = RANDOMOSC_TOKEN_T;
            }
            else if (strcmp(value, "terrainosc") == 0) {
                out[x].tt = TERRAINOSC_TOKEN_T;
            }
            else if(strcmp(value, "lowpassfilter") == 0) {
                out[x].tt = LOWPASSFILTERTOKEN_TOKEN_T;
            }
            else if(strcmp(value, "highpassfilter") == 0) {
                out[x].tt = HIGHPASSFILTERTOKEN_TOKEN_T;
            }
            else if(strcmp(value, "inputa") == 0) {
                out[x].tt = INPUTA_TOKEN_T;
            }
            else if(strcmp(value, "inputb") == 0) {
                out[x].tt = INPUTB_TOKEN_T;
            }
            else if(strcmp(value, "inputc") == 0) {
                out[x].tt = INPUTC_TOKEN_T;
            }
            else if(strcmp(value, "inputd") == 0) {
                out[x].tt = INPUTD_TOKEN_T;
            }
            else if(strcmp(value, "MAIN") == 0) {
                out[x].tt = MAIN_TOKEN_T;
            }
            else if(strcmp(value, "stepsequencer") == 0) {
                out[x].tt = STEPSEQ_TOKEN_T;
            }
            else if(strcmp(value, "random") == 0) {
                out[x].tt = RANDOM_TOKEN_T;
            }
            else if(strcmp(value, "randomint") == 0) {
                out[x].tt = RANDOMINT_TOKEN_T;
            }
            else if(strcmp(value, "linenvelope") == 0) {
                out[x].tt = LINENVELOPEGENERATORTOKEN_TOKEN_T;
            }
        }
    } 
}

char* tokenTypeToString(TokenType input) {
    char* out;
    switch (input) {
    case IDENTIFIER_TOKEN_T:
        out = "Identifier";
        break;
    case NUMBER_TOKEN_T:
        out = "Number";
        break;
    case FUNCTION_TOKEN_T:
        out = "Function";
        break;
    case SEMICOLON_TOKEN_T:
        out = "Semicolon";
        break;
    case BRACKETLEFT_TOKEN_T:
        out = "Bracketsleft";    
        break;
    case BRACKETRIGHT_TOKEN_T:
        out = "Bracketright";    
        break;
    case PARANTHESISLEFT_TOKEN_T:
        out = "Paranthesisleft";    
        break;
    case PARANTHESISRIGHT_TOKEN_T:
        out = "Paranthesisright";    
        break;
    case SQUAREBRACKETLEFT_TOKEN_T:
        out = "Squarebracketleft";
        break;
    case SQUAREBRACKETRIGHT_TOKEN_T:
        out = "Squarebracketright";
        break;
    case ASSIGN_TOKEN_T:
        out = "Assign";
        break;
    case PLUS_TOKEN_T:
        out = "Plus";
        break;
    case MINUS_TOKEN_T:
        out = "Minus";
        break;
    case MULTIPLY_TOKEN_T:
        out = "Multiply";
        break;
    case DIVIDE_TOKEN_T:
        out = "Divide";
        break;
    case FOR_TOKEN_T:
        out = "For";
        break;
    case IF_TOKEN_T:
        out = "If";
        break;
    case COMMA_TOKEN_T:
        out = "Comma";
        break;
    case WHILE_TOKEN_T:
        out = "While";
        break;
    case SAWOSC_TOKEN_T:
        out = "SawtoothOscillator";
        break;
    case SINEOSC_TOKEN_T:
        out = "SineOscillator";
        break;
    case WAVEOSC_TOKEN_T:
        out = "WaveOscillator";
        break;
	case TRUESINEOSC_TOKEN_T:
		out = "TruesineOscillator";
		break;
    case SQUAREOSC_TOKEN_T:
        out = "SquareOscillator";
        break;
    case TRIANGLEOSC_TOKEN_T:
        out = "TriangleOscillator";
        break;
    case TERRAINOSC_TOKEN_T:
        out = "TerrainOscillator";
        break;
    case STEPSEQ_TOKEN_T:
        out = "StepSequencer";
        break;
    case LOWPASSFILTERTOKEN_TOKEN_T:
        out = "LowpassFilter";
        break;
    case HIGHPASSFILTERTOKEN_TOKEN_T:
        out = "HighpassFilter";
        break;
    case RANDOMOSC_TOKEN_T:
        out = "RandomOscillator";
        break;
    case RETURN_TOKEN_T:
        out = "Return";
        break;
    case SMALLER_TOKEN_T:
        out = "Smaller";
        break;
    case GREATER_TOKEN_T:
        out = "Greater";
        break;
    case INPUTA_TOKEN_T:
        out = "InputA";
        break;
    case INPUTB_TOKEN_T:
        out = "InputB";
        break;
    case INPUTC_TOKEN_T:
        out = "InputC";
        break;
    case INPUTD_TOKEN_T:
        out = "InputD";
        break;
    case NOTEMARKER_TOKEN_T:
        out = "Notemarker";
        break;
    case RANDOM_TOKEN_T:
        out = "Random";
        break;
    case RANDOMINT_TOKEN_T:
        out = "RandomInt";
        break;
    case LINENVELOPEGENERATORTOKEN_TOKEN_T:
        out = "LinearEnvelopeGenerator";
        break;
    default:
        out = "Unknown";
        break;
    }

    return out;
}
