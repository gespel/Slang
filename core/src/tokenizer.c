#include <ctype.h>
#include "../include/tokenizer.h"

//
// Created by sten on 11.06.24.
//

Token* tokenize(char* input, int* length) {
  Token* out = malloc(1024*sizeof(Token));
  char* t;
  int i = 0;
  t = strtok(input, " ");
  while(t != NULL) {
    if(!isdigit(t[0])) {
      Token temp;
      temp.tt = IDENTIFIER;
      temp.value = t;
      out[i] = temp;
    }
    else {
      char* ns = malloc(sizeof(char)*128);
      for(int k = 0; k < strlen(t); k++) {
        if(isdigit(t[k])) {
          ns[k] = t[k];
        }
        else {
          printf("Unexpected token!\n");
          exit(-1);
        }
      }
      ns[strlen(t)] = '\0';
      Token temp;
      temp.tt = NUMBER;
      temp.value = t;
      out[i] = temp;
    }

    i++;
    t = strtok(NULL, " ");
  }

  for(int x = 0; x < i; x++) {
    if(out[x].tt == IDENTIFIER) {
      if(strcmp(out[x].value, "fn") == 0) {
        out[x].tt = FUNCTION;
      }
    }
  }
  *length = i;
  return out;
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
    default:
      out = "Unknown";
      break;
  }

  return out;
}