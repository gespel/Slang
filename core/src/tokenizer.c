#include <ctype.h>
#include "../include/tokenizer.h"

//
// Created by sten on 11.06.24.
//

Token* tokenize(char* input, int* length) {
	Token* out = malloc(1024*sizeof(Token));
	char* tokenString;
  	int tokenCount = 0;
  	tokenString = strtok(input, " ");
  	while(tokenString != NULL) {
        for(size_t j = 0; j < strlen(tokenString); j++) {
            //printf("lexing char: %c\n", tokenString[j]);
            if(isalpha(tokenString[j])) {
                char* ns = malloc(sizeof(char)*128);
                while(isalpha(tokenString[j])) {
                    ns[j] = tokenString[j];
                    j++;
                }
                j--;

                Token temp;
                temp.tt = IDENTIFIER;
                temp.value = ns;
                out[tokenCount] = temp;
                tokenCount++;
            }
            else if(tokenString[j] == ';') {
                Token temp;
                temp.tt = SEMICOLON;
                char *tmpString = malloc(sizeof(char) * 2);
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
                out[tokenCount] = temp;
                tokenCount++;
            }
            else if(tokenString[j] == '=') {
                Token temp;
                temp.tt = ASSIGN;
                char *tmpString = malloc(sizeof(char) * 2);
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
                out[tokenCount] = temp;
                tokenCount++;
            }
            else if(tokenString[j] == '(') {
                Token temp;
                temp.tt = PARANTHESISLEFT;
                char *tmpString = malloc(sizeof(char) * 2);
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
                out[tokenCount] = temp;
                tokenCount++;
            }
            else if(tokenString[j] == ')') {
                Token temp;
                temp.tt = PARANTHESISRIGHT;
                char *tmpString = malloc(sizeof(char) * 2);
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
                out[tokenCount] = temp;
                tokenCount++;
            }
            else if(tokenString[j] == '{') {
                Token temp;
                temp.tt = BRACKETLEFT;
                char *tmpString = malloc(sizeof(char) * 2);
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
                out[tokenCount] = temp;
                tokenCount++;
            }
            else if(tokenString[j] == '}') {
                Token temp;
                temp.tt = BRACKETRIGHT;
                char *tmpString = malloc(sizeof(char) * 2);
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
                out[tokenCount] = temp;
                tokenCount++;
            }
            else if(tokenString[j] == '+') {
                Token temp;
                temp.tt = PLUS;
                char *tmpString = malloc(sizeof(char) * 2);
                tmpString[0] = tokenString[j];
                tmpString[1] = '\0';
                temp.value = tmpString;
                out[tokenCount] = temp;
                tokenCount++;
            }
            else if(isdigit(tokenString[j])) {
                char* ns = malloc(sizeof(char)*128);
                while(isdigit(tokenString[j])) {
                    ns[j] = tokenString[j];
                    j++;
                }
                j--;

                Token temp;
                temp.tt = NUMBER;
                temp.value = ns;
                out[tokenCount] = temp;
                tokenCount++;
            }
        }
        tokenString = strtok(NULL, " ");
    }

    tokenizeStrings(out, tokenCount);

    *length = tokenCount;
    
    return out;
}

void tokenizeStrings(Token* out, int numTokens) {
    for(int x = 0; x < numTokens; x++) {
        if(out[x].tt == IDENTIFIER) {
            if(strcmp(out[x].value, "fn") == 0) {
                out[x].tt = FUNCTION;
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
    default:
        out = "Unknown";
        break;
    }

    return out;
}
