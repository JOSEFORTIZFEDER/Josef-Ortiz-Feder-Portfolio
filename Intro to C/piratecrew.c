/*
 * Josef Ortiz-Feder
 * 9/6/2020
 * Program 2 - Pirate Crew Recruitment
*/
#include <stdio.h>
#include <math.h>
#define MINIMUM_SWIMMING_DISTANCE 100
int main(void)
{
  // Data Dictionary
  char treasure_input, swim_input;
  int distance_input;

  // Getting input for a character
  printf("Do you like digging for treasure?\n");
  scanf(" %c", &treasure_input);

  // Getting input for another character
  printf("Are you able to swim?\n");
  scanf(" %c", &swim_input);

  // If statement that checks if swin_input is y or Y
  if(swim_input == 'y' || swim_input == 'Y')
  {
    // Getting input for an integer
    printf("How many meters are you able to swim?\n");
    scanf("%d", &distance_input);

    // If statement that checks if treasure_input is y or Y and if distance_input is high enough
    if(treasure_input == 'y' || treasure_input == 'Y' && distance_input >= MINIMUM_SWIMMING_DISTANCE)
    {
      printf("You may join the pirate crew! Arrr!\n");
    }

    else
    {
        printf("You may not join the crew.\n");
    }

  }
  else
  {
    printf("You may not join the crew.\n");
  }

}
