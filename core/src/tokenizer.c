#include <ctype.h>
#include "../include/tokenizer.h"

//
// Created by sten on 11.06.24.
//

Token* tokenize(char* input, int* length) {
	Token* out = malloc(1024*sizeof(Token));
	char* tokenString;
  	int tokenCount = 0;
  	tokenString = strtok(input, " \n\t\r");
  	while(tokenString != NULL) {
        for(size_t j = 0; j < strlen(tokenString); j++) {
            Token temp;
            char *tmpString = malloc(sizeof(char) * 2);

            //printf("lexing char: %c\n", tokenString[j]);
            if(isalpha((unsigned char)tokenString[j])) {
                char* ns = calloc(128, sizeof(char));
                int nsc = 0;
                while(isalpha((unsigned char)tokenString[j])) {
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
            else if(isdigit((unsigned char)tokenString[j])) {
                //printf("DIGIT found! %c\n", tokenString[j]);
                char* ns = malloc(sizeof(char)*128);
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
        out = "SawtoothOscilator";
        break;
    case SINEOSC:
        out = "SineOscilator";
        break;
    default:
        out = "Unknown";
        break;
    }

    return out;
}
