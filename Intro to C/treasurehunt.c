/*
 * Josef Ortiz-Feder
 * 12/4/2020
 * Program 8 - Treasure Hunt
*/

#include <stdio.h>

// Constants
#define NUMPIRATES 4
#define NUMHOURS 8

// Pirate and Map structures (already given)
struct pirate
{
  int dig;
  int carry;
};

struct map
{
  int sand;
  int treasure;
};

// Function Signatures
void printmap(struct map treasure_map[3][3]);
int isClear(struct map treasure_map[3][3]);



int main()
{
  // Data Dictionary
  int i, j, k, x, y, total_treasure=0;
  struct map treasure_map[3][3];
  struct pirate pirates[NUMPIRATES];

  // Prompt the user for the file name
  char file_name[30];
  printf("You have arrived at Treasure Island!\n");
  printf("What is the name of your map?\n");
  scanf("%s", &file_name);
  printf("\n");
  FILE *ifp = fopen(file_name, "r");

  // Put the information from the file into a 3x3 map
  for(i = 0; i < 3; ++i)
  {
    for(j = 0; j < 3; ++j)
    {
      fscanf(ifp, "%d", &treasure_map[i][j].sand);
      fscanf(ifp, "%d", &treasure_map[i][j].treasure);
    }
  }

  // Put the information from the file into an array of pirates
  for(i = 0; i < NUMPIRATES; ++i)
  {
    fscanf(ifp, "%d", &pirates[i].dig);
    fscanf(ifp, "%d", &pirates[i].carry);
  }

  // For loop that runs the program 8 times
  for(i = 0; i < NUMHOURS; ++i)
  {
    // Print out the start of day information
    printf("You have %d hours left to dig up the treasure.\n", NUMHOURS - i);
    printf("Crew    Dig     Carry\n");
    for(j = 1; j <= NUMPIRATES; ++j)
    {
      printf("%d\t%d\t%d\n", j, pirates[j-1].dig, pirates[j-1].carry);
    }
    // For loop that runs for each pirate
    for(j = 0; j < NUMPIRATES; ++j)
    {
      printf("\nWhere would you like to send crew member %d?\n", j+1);
      // Printmap function that outputs the current map
      printmap(treasure_map);

      // Prompt the user for location to send pirate
      scanf("%d", &x);
      scanf("%d", &y);

      // Set of if and else statements that determine the situation where the user sends a pirate
      if(treasure_map[x-1][y-1].treasure <= 0)
      {
        printf("\nThis section has already been cleared.\n");
      }
      else if(treasure_map[x-1][y-1].sand <= 0)
      {
        // Add to the total treasure to be outputted later
        total_treasure += pirates[j].carry;
        treasure_map[x-1][y-1].treasure -= pirates[j].carry;
        if(treasure_map[x-1][y-1].treasure < 0)
        {
          total_treasure += treasure_map[x-1][y-1].treasure;
        }
        if(treasure_map[x-1][y-1].treasure <= 0)
        {
          printf("\nYou take all of the treasure back to the ship!\n");
        }
        else
        {
          printf("\nYou take some of the treasure back to the ship!\n");
        }
      }
      else
      {
        treasure_map[x-1][y-1].sand -= pirates[j].dig;
        if(treasure_map[x-1][y-1].sand <= 0)
        {
          printf("\nYou have removed all of the sand from this section!\n");
        }
        else
        {
          printf("\nYou have removed some of the sand from this section!\n");
        }
      }
      // Test if the treasure map is cleared out and output the victory message
      if(isClear(treasure_map) == 0)
      {
        printf("\nAll of the pirate's treasure belongs to you now!\n");
        break;
      }

    }
    // I'm forced to put this here so I can break the big for loop
    if(isClear(treasure_map) == 0)
    {
      break;
    }
  }
  // Test case if the treasure map did not end up getting cleared out
  if(isClear(treasure_map) == 1)
  {
    printf("\nYou are forced to evacuate the island. You have claimed %d pieces of the pirate's treasure!\n", total_treasure);
  }
  
  fclose(ifp);
  return 0;

}
// Printmap function that outputs the map for the user
void printmap(struct map treasure_map[3][3])
{
  int i, j;
  for(i = 0; i < 3; ++i)
  {
    for(j = 0; j < 3; ++j)
    {
      if(treasure_map[i][j].sand <= 0)
      {
        if(treasure_map[i][j].treasure <= 0)
        {
          printf("-\t");
        }
        else
        {
          printf("%dT\t", treasure_map[i][j].treasure);
        }
      }
      else
      {
        printf("%ds\t", treasure_map[i][j].sand);
      }
    }
    printf("\n");
  }
}
// isClear method that determines whether or not the map is cleared
int isClear(struct map treasure_map[3][3])
{
  int i, j;
  for(i = 0; i < 3; ++i)
  {
    for(j = 0; j < 3; ++j)
    {
      if(treasure_map[i][j].treasure > 0)
      {
        return 1;
      }
    }
  }
  return 0;
}
