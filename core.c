#include "core.h"

//
// Created by sten on 11.06.24.
//
int main() {
  char a[] = "Sten ist fn";
  int length = 0;
  Token* out = tokenize(a, &length);
  printf("%d tokens!\n", length);
  printf("%s\n", tokenTypeToString(out[0].tt));
  printf("%s\n", tokenTypeToString(out[1].tt));
  printf("%s\n", tokenTypeToString(out[2].tt));
  free(out);
}

Token* tokenize(char* input, int* length) {
  Token* out = malloc(1024*sizeof(Token));

  char* t;
  int i = 0;
  t = strtok(input, " ");
  while(t != NULL) {
    Token temp;
    temp.tt = IDENTIFIER;
    temp.value = t;
    out[i] = temp;
    i++;
    t = strtok(NULL, " ");
  }

  for(int x = 0; x < i; x++) {
    if(strcmp(out[x].value, "fn") == 0) {
      out[x].tt = FUNCTION;
    }
  }
  *length = i;
  return out;
}

char* tokenTypeToString(TokenType input) {
  char* out = malloc(sizeof(char)*64);

  if(input == FUNCTION) {
    out = "Function";
  }
  else if(input == IDENTIFIER) {
    out = "Identifier";
  }

  return out;
}