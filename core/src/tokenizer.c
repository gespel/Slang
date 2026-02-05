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

                temp.tt = TOKEN_IDENTIFIER;
                temp.value = ns;
                //printf("Tokenzier registered identifier: %s\n", ns);
            }
            else if(tokenString[j] == ';') {
                temp.tt = TOKEN_SEMICOLON;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '=') {
                temp.tt = TOKEN_ASSIGN;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '(') {
                //printf("Opening PARANTHESISLEFT found!\n");
                temp.tt = TOKEN_PARANTHESISLEFT;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == ')') {
                temp.tt = TOKEN_PARANTHESISRIGHT;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '{') {
                temp.tt = TOKEN_BRACKETLEFT;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '}') {
                temp.tt = TOKEN_BRACKETRIGHT;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '[') {
                temp.tt = TOKEN_SQUAREBRACKETLEFT;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == ']') {
                temp.tt = TOKEN_SQUAREBRACKETRIGHT;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '+') {
                temp.tt = TOKEN_PLUS;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '-') {
                temp.tt = TOKEN_MINUS;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '*') {
                temp.tt = TOKEN_MULTIPLY;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '/') {
                temp.tt = TOKEN_DIVIDE;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;

            }
            else if(tokenString[j] == '>') {
                temp.tt = TOKEN_GREATER;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '<') {
                temp.tt = TOKEN_SMALLER;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == ',') {
                temp.tt = TOKEN_COMMA;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if (tokenString[j] == '$') {
                temp.tt = TOKEN_NOTEMARKER;
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

                temp.tt = TOKEN_NUMBER;
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
        if(out[x].tt == TOKEN_IDENTIFIER) {
            char* value = out[x].value;
            if(strcmp(value, "fn") == 0) {
                out[x].tt = TOKEN_FUNCTION;
            }
            else if(strcmp(value, "for") == 0) {
                out[x].tt = TOKEN_FOR;
            }
            else if(strcmp(value, "if") == 0) {
                out[x].tt = TOKEN_IF;
            }
            else if(strcmp(value, "return") == 0) {
                out[x].tt = TOKEN_RETURN;
            }
            else if(strcmp(value, "while") == 0) {
                out[x].tt = TOKEN_WHILE;
            }
            else if(strcmp(value, "sineosc") == 0) {
                out[x].tt = TOKEN_SINEOSC;
            }
            else if(strcmp(value, "sawtoothosc") == 0) {
                out[x].tt = TOKEN_SAWOSC;
            }
            else if(strcmp(value, "wavetableosc") == 0) {
                out[x].tt = TOKEN_WAVEOSC;
            }
			else if(strcmp(value, "truesineosc") == 0) {
				out[x].tt = TOKEN_TRUESINEOSC;
			}
            else if (strcmp(value, "squareosc") == 0) {
                out[x].tt = TOKEN_SQUAREOSC;
            }
            else if (strcmp(value, "triangleosc") == 0) {
                out[x].tt = TOKEN_TRIANGLEOSC;
            }
            else if (strcmp(value, "randomosc") == 0) {
                out[x].tt = TOKEN_RANDOMOSC;
            }
            else if (strcmp(value, "terrainosc") == 0) {
                out[x].tt = TOKEN_TERRAINOSC;
            }
            else if(strcmp(value, "lowpassfilter") == 0) {
                out[x].tt = TOKEN_LOWPASSFILTER;
            }
            else if(strcmp(value, "highpassfilter") == 0) {
                out[x].tt = TOKEN_HIGHPASSFILTER;
            }
            else if(strcmp(value, "inputa") == 0) {
                out[x].tt = TOKEN_INPUTA;
            }
            else if(strcmp(value, "inputb") == 0) {
                out[x].tt = TOKEN_INPUTB;
            }
            else if(strcmp(value, "inputc") == 0) {
                out[x].tt = TOKEN_INPUTC;
            }
            else if(strcmp(value, "inputd") == 0) {
                out[x].tt = TOKEN_INPUTD;
            }
            else if(strcmp(value, "MAIN") == 0) {
                out[x].tt = TOKEN_MAIN;
            }
            else if(strcmp(value, "stepsequencer") == 0) {
                out[x].tt = TOKEN_STEPSEQ;
            }
            else if(strcmp(value, "random") == 0) {
                out[x].tt = TOKEN_RANDOM;
            }
            else if(strcmp(value, "randomint") == 0) {
                out[x].tt = TOKEN_RANDOMINT;
            }
            else if(strcmp(value, "linenvelope") == 0) {
                out[x].tt = TOKEN_LINENVELOPE;
            }
        }
    } 
}

char* tokenTypeToString(TokenType input) {
    char* out;
    switch (input) {
    case TOKEN_IDENTIFIER:
        out = "Identifier";
        break;
    case TOKEN_NUMBER:
        out = "Number";
        break;
    case TOKEN_FUNCTION:
        out = "Function";
        break;
    case TOKEN_SEMICOLON:
        out = "Semicolon";
        break;
    case TOKEN_BRACKETLEFT:
        out = "Bracketsleft";    
        break;
    case TOKEN_BRACKETRIGHT:
        out = "Bracketright";    
        break;
    case TOKEN_PARANTHESISLEFT:
        out = "Paranthesisleft";    
        break;
    case TOKEN_PARANTHESISRIGHT:
        out = "Paranthesisright";    
        break;
    case TOKEN_SQUAREBRACKETLEFT:
        out = "Squarebracketleft";
        break;
    case TOKEN_SQUAREBRACKETRIGHT:
        out = "Squarebracketright";
        break;
    case TOKEN_ASSIGN:
        out = "Assign";
        break;
    case TOKEN_PLUS:
        out = "Plus";
        break;
    case TOKEN_MINUS:
        out = "Minus";
        break;
    case TOKEN_MULTIPLY:
        out = "Multiply";
        break;
    case TOKEN_DIVIDE:
        out = "Divide";
        break;
    case TOKEN_FOR:
        out = "For";
        break;
    case TOKEN_IF:
        out = "If";
        break;
    case TOKEN_COMMA:
        out = "Comma";
        break;
    case TOKEN_WHILE:
        out = "While";
        break;
    case TOKEN_SAWOSC:
        out = "SawtoothOscillator";
        break;
    case TOKEN_SINEOSC:
        out = "SineOscillator";
        break;
    case TOKEN_WAVEOSC:
        out = "WaveOscillator";
        break;
	case TOKEN_TRUESINEOSC:
		out = "TruesineOscillator";
		break;
    case TOKEN_SQUAREOSC:
        out = "SquareOscillator";
        break;
    case TOKEN_TRIANGLEOSC:
        out = "TriangleOscillator";
        break;
    case TOKEN_TERRAINOSC:
        out = "TerrainOscillator";
        break;
    case TOKEN_STEPSEQ:
        out = "StepSequencer";
        break;
    case TOKEN_LOWPASSFILTER:
        out = "LowpassFilter";
        break;
    case TOKEN_HIGHPASSFILTER:
        out = "HighpassFilter";
        break;
    case TOKEN_RANDOMOSC:
        out = "RandomOscillator";
        break;
    case TOKEN_RETURN:
        out = "Return";
        break;
    case TOKEN_SMALLER:
        out = "Smaller";
        break;
    case TOKEN_GREATER:
        out = "Greater";
        break;
    case TOKEN_INPUTA:
        out = "InputA";
        break;
    case TOKEN_INPUTB:
        out = "InputB";
        break;
    case TOKEN_INPUTC:
        out = "InputC";
        break;
    case TOKEN_INPUTD:
        out = "InputD";
        break;
    case TOKEN_NOTEMARKER:
        out = "Notemarker";
        break;
    case TOKEN_RANDOM:
        out = "Random";
        break;
    case TOKEN_RANDOMINT:
        out = "RandomInt";
        break;
    case TOKEN_LINENVELOPE:
        out = "LinearEnvelopeGenerator";
        break;
    default:
        out = "Unknown";
        break;
    }

    return out;
}
