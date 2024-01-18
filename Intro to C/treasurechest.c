/*
 * Josef Ortiz-Feder
 * 10/23/2020
 * Program 6 - Treasure Chest
*/

#include <stdio.h>
#define ARRAY_LENGTH 7

int main()
{
  // Data Dictionary
  char file_name[50];
  int treasure_combo[ARRAY_LENGTH], treasure_guess[ARRAY_LENGTH];
  int test = 0, array_input, dupe_key = 0, no_key, some_key = 0, good_key = 1;

  // Prompt the user for the text file
  printf("Please enter the name of the treasure chest file:\n");
  scanf("%s", &file_name);
  FILE *ifp = fopen(file_name, "r");

  // Take the data from the file and put it into an array to be tested
  printf("\n\n\nTo get to me treasure you'll have to figure out which of me 100 keys are used in the 7 locks of me treasure chest.\n");
  for(int i = 0; i < ARRAY_LENGTH; ++i)
  {
    fscanf(ifp, "%d", &treasure_combo[i]);
  }

  // While loop that runs the menu
  while(test == 0)
  {
    // Prompt the user for their guesses on the treasure chest
    printf("\nWhich keys will ye use?\n");
    for(int i = 0; i < ARRAY_LENGTH; ++i)
    {
      scanf("%d", &array_input);
      // For loop that will determine if there are any duplicates within the guess
      for(int j = 0; j < ARRAY_LENGTH; ++j)
      {
        // If there is a duplicate, then set dupe_key to 1
        if(treasure_guess[j] == array_input)
        {
          dupe_key = 1;
        }
      }
      treasure_guess[i] = array_input;
    }
    // Nested for loops that will test for the relationships between the treasure combo and the treasure guess arrays
    for(int i = 0; i < ARRAY_LENGTH; ++i)
    {
      for(int j = 0; j < ARRAY_LENGTH; ++j)
      {
        // If the guess is in the actual combo, then add to some_key to be outputted later
        if(treasure_guess[i] == treasure_combo[j])
        {
          some_key += 1;
        }
      }
      // If the guess and the combo are the same, then set good_key to 0 to be outputted later
      if(treasure_guess[i] != treasure_combo[i])
      {
        good_key = 0;
      }

    }

    // These series of if statements are testing for values and are outputted accordingly

    // If the good_key variable is still at 1, then end the program as the guess is correct
    if(good_key == 1)
    {
      break;
    }

    // If the dupe_key variable has changed, then output the corresponding text
    else if(dupe_key != 0)
    {
      printf("You can only use each key once, matey!\n");
    }

    // If the some_key variable has changed, then output the corresponding text
    else if(some_key != 0)
    {
      printf("%d of those keys are correct, matey! But are they in the right order?\n", some_key);
    }

    // If the some_key variable has not changed, then output the corresponding text
    if(some_key == 0)
    {
      printf("Hah! None of those keys will work!\n");
    }

    // Reset the keys for the next loop
    good_key = 1;
    some_key = 0;
    dupe_key = 0;

    // Reset the guess values so that the dupe_key check doesn't accidently flag it
    for(int i = 0; i < ARRAY_LENGTH; ++i)
    {
      treasure_guess[i] = -i;
    }
  }

  // Output once the program ends
  printf("Arr! You've opened me treasure chest and found...\nA map! To the rest of me treasure on Treasure Island.\nHahaha!\n");

  // Close the file
  fclose(ifp);

  // Return 0
  return 0;
}
