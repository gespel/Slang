#include <ctype.h>
#include "../include/tokenizer.h"

//
// Created by sten on 11.06.24.
//

Token* tokenize(char* input, int* length) {
    char *cleaned = calloc(strlen(input), sizeof(char));
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

	Token* out = malloc(1024*sizeof(Token));
	char* tokenString;
  	int tokenCount = 0;
  	tokenString = strtok(cleaned, " \n\t\r");
  	while(tokenString != NULL) {
        for(size_t j = 0; j < strlen(tokenString); j++) {
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

                temp.tt = IDENTIFIER;
                temp.value = ns;
            }
            else if(tokenString[j] == ';') {
                temp.tt = SEMICOLON;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '=') {
                temp.tt = ASSIGN;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '(') {
                //printf("Opening PARANTHESISLEFT found!\n");
                temp.tt = PARANTHESISLEFT;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == ')') {
                temp.tt = PARANTHESISRIGHT;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '{') {
                temp.tt = BRACKETLEFT;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '}') {
                temp.tt = BRACKETRIGHT;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '+') {
                temp.tt = PLUS;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '-') {
                temp.tt = MINUS;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '*') {
                temp.tt = MULTIPLY;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '/') {
                temp.tt = DIVIDE;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;

            }
            else if(tokenString[j] == '>') {
                temp.tt = GREATER;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == '<') {
                temp.tt = SMALLER;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(tokenString[j] == ',') {
                temp.tt = COMMA;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if (tokenString[j] == '$') {
                temp.tt = NOTEMARKER;
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
            }
            else if(isdigit((unsigned char)tokenString[j])) {
                //printf("DIGIT found! %c\n", tokenString[j]);
                char* ns = calloc(128, sizeof(char));
                int nsc = 0;
                while(isdigit((unsigned char)tokenString[j])) {
                    //printf("%c is a digit\n", tokenString[j]);
                    ns[nsc] = tokenString[j];
                    j++;
                    nsc++;
                }
                j--;

                temp.tt = NUMBER;
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
        if(out[x].tt == IDENTIFIER) {
            char* value = out[x].value;
            if(strcmp(value, "fn") == 0) {
                out[x].tt = FUNCTION;
            }
            else if(strcmp(value, "for") == 0) {
                out[x].tt = FOR;
            }
            else if(strcmp(value, "if") == 0) {
                out[x].tt = IF;
            }
            else if(strcmp(value, "return") == 0) {
                out[x].tt = RETURN;
            }
            else if(strcmp(value, "while") == 0) {
                out[x].tt = WHILE;
            }
            else if(strcmp(value, "sineosc") == 0) {
                out[x].tt = SINEOSC;
            }
            else if(strcmp(value, "sawtoothosc") == 0) {
                out[x].tt = SAWOSC;
            }
            else if(strcmp(value, "wavetableosc") == 0) {
                out[x].tt = WAVEOSC;
            }
			else if(strcmp(value, "truesineosc") == 0) {
				out[x].tt = TRUESINEOSC;
			}
            else if (strcmp(value, "squareosc") == 0) {
                out[x].tt = SQUAREOSC;
            }
            else if(strcmp(value, "inputa") == 0) {
                out[x].tt = INPUTA;
            }
            else if(strcmp(value, "inputb") == 0) {
                out[x].tt = INPUTB;
            }
            else if(strcmp(value, "inputc") == 0) {
                out[x].tt = INPUTC;
            }
            else if(strcmp(value, "inputd") == 0) {
                out[x].tt = INPUTD;
            }
        }
    } 
}

char* tokenTypeToString(TokenType input) {
    char* out;
    switch (input) {
    case IDENTIFIER:
        out = "Identifier";
        break;
    case NUMBER:
        out = "Number";
        break;
    case FUNCTION:
        out = "Function";
        break;
    case SEMICOLON:
        out = "Semicolon";
        break;
    case BRACKETLEFT:
        out = "Bracketsleft";    
        break;
    case BRACKETRIGHT:
        out = "Bracketright";    
        break;
    case PARANTHESISLEFT:
        out = "Paranthesisleft";    
        break;
    case PARANTHESISRIGHT:
        out = "Paranthesisright";    
        break;
    case ASSIGN:
        out = "Assign";
        break;
    case PLUS:
        out = "Plus";
        break;
    case MINUS:
        out = "Minus";
        break;
    case MULTIPLY:
        out = "Multiply";
        break;
    case DIVIDE:
        out = "Divide";
        break;
    case FOR:
        out = "For";
        break;
    case IF:
        out = "If";
        break;
    case COMMA:
        out = "Comma";
        break;
    case WHILE:
        out = "While";
        break;
    case SAWOSC:
        out = "SawtoothOscillator";
        break;
    case SINEOSC:
        out = "SineOscillator";
        break;
    case WAVEOSC:
        out = "WaveOscillator";
        break;
	case TRUESINEOSC:
		out = "TruesineOscillator";
		break;
    case SQUAREOSC:
        out = "SquareOscillator";
        break;
    case INPUTA:
        out = "InputA";
        break;
    case INPUTB:
        out = "InputB";
        break;
    case INPUTC:
        out = "InputC";
        break;
    case INPUTD:
        out = "InputD";
        break;
    case NOTEMARKER:
        out = "Notemarker";
        break;
    default:
        out = "Unknown";
        break;
    }

    return out;
}
