#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include <stdbool.h>

#define MAX_STR_SZ 256

int main(int argc, char *argv[])
{

  //Choose random number
  srand(time(0));
  int randomNumber = (rand() % (909 - 1 + 1)) + 1;

  //Set variables up
  int attemptsLeft = 10;
  int attempts = 0;
  char invalidLetters[26];
  char* buffer;
  long lSize;
  int wordLength;
  int i = 0;
  char* input;

  //Open 'words.txt'
  FILE* list = fopen("words.txt", "rb");

  //Get size of 'words.txt'
  fseek(list, 0, SEEK_END);
  lSize = ftell(list);
  rewind(list);

  char* word[lSize];

  //Allocate memory
  buffer = (char*)calloc( 1, lSize + 1);
  if (!buffer) {
    fclose(list), fputs("Memory alloc failed.", stderr), exit(0);
    }

  //Put the content of 'words.txt' in the buffer
  if ( 1!=fread(buffer, lSize, 1, list))
    fclose(list), free(buffer), fputs("Couldn't fing 'words.txt' file.", stderr), exit(0);


  char* p = strtok(buffer, "\n");

  //Put every word in an array
  while (p != NULL) {
    word[i++] = p;
    p = strtok(NULL, "\n");
    word[strlen (*word) - 1] = "\0";
  }

  wordLength = strlen(word[randomNumber]) - 1;

  char* foundChars = calloc(wordLength, sizeof(char));

  printf("Guess the word!\n");

  //Print the first row of '#'
  for (int j = 0; j < wordLength; j++) {
    if (j != wordLength-1)
      printf("#");
    else
      printf("#\n");
  }

  while (attemptsLeft != 0) {

    //Empty the input
    input = (char*) malloc(MAX_STR_SZ);
    if (input == NULL) {
      printf("No memory\n");
      exit(0); }

    fgets(input, MAX_STR_SZ, stdin);

    //Remove EOL character at the end of the input
    if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n')) {
      input[strlen (input) - 1] = '\0';
    }

    //Remove \r character at the end of the word
    if ((strlen(word[randomNumber]) > 0) && (word[randomNumber][strlen (word[randomNumber]) - 1] == '\r')) {
      word[randomNumber][strlen (word[randomNumber]) - 1] = '\0';

    }

    //Check if the input is the same as the word, or if it's a part of it
    if (strcmp(input, word[randomNumber]) == 0) {
      attempts++;
      printf("You found the word '%s' in %d attempt(s)!", word[randomNumber], attempts);
      break;
    }
    else {
      if (strlen(input) == 1) {
        if (strchr(word[randomNumber], (int)*input) != 0) {

          if (strchr(foundChars, *input) == NULL) {
            strcat(foundChars, input);
            attempts++;
            printf("%s is a part of the word!\n", input);
          }
          else {
            printf("You already found the letter '%s'!\n", input);
          }
        }
        else {
          if (strchr(invalidLetters, *input) == NULL) {
            attemptsLeft--;
            attempts++;
            strcat(invalidLetters, input);
            printf("'%s' is not part of the word! You have %d attempts left.\n", input, attemptsLeft); }
          else {
            printf("You already tried this letter, and it is still wrong!\n");
          }
        }

          //Check if all the letters have been found
          if (CheckWord(foundChars, word[randomNumber]) == true) {
            printf("You found the word %s in %d attempt(s)!", word[randomNumber], attempts);
            break;
          }

          //Display found letters
          DisplayLetters(input[0], word[randomNumber], foundChars, wordLength);

      }
      else if (input != NULL){
        printf("%s is not the word! You have %d attempts left.\n", input, attemptsLeft);
        attemptsLeft--;
        attempts++;
      }
      else {
        printf("Please enter a single letter or the full word.");
      }
    }
  }
  if (attemptsLeft == 0) {
  printf("You lost! The word was %s.",word[randomNumber]); }
}
