#ifndef DEF_MAIN

#define DEF_MAIN

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void DisplayLetters(char input, char* word, char* foundChars, int wordLength) {

  for (int i = 0; i < wordLength; i++) {


    if (strchr(foundChars, word[i]) != NULL) {
      printf("%c", word[i]);
    }
    else {
      printf("#");
    }

    if (i == wordLength-1) {
      printf("\n");
    }

}
}

bool CheckWord(char* foundChars, char* word) {

  for (int i = 0; i < strlen(word); i++) {
    if (strchr(foundChars, word[i]) == NULL) {
      return false;
    }
    }
  return true; }

#endif
