#include "core.h"

//
// Created by sten on 11.06.24.
//
int main() {
  char a[] = "Sten ist fn";
  Token* out = tokenize(a);
  printf("%s", out[0].value);
  printf("%s", out[1].value);
  printf("%s", tokenTypeToString(out[2].tt));
  free(out);
}

Token* tokenize(char* input) {
  Token* out = malloc(1024*sizeof(Token));

  char* t;
  int i = 0;
  t = strtok(input, " ");
  while(t != NULL) {
    printf("%s\n", t);
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

  return out;
}

char* tokenTypeToString(TokenType input) {
  char* out = malloc(sizeof(char)*64);

  if(input == FUNCTION) {
    out = "Function";
  }

  return out;
}