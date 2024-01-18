/* Josef Ortiz-Feder
 * 8/30/2020
 * Program 1 - How many oranges does it take to get to the Caribbean from Spain
 */
#include <stdio.h>
#include <math.h>
#define TRAVEL_DISTANCE 7228
#define ORANGES_PER_MEMBER 0.5

int main(void)
{
  // Variables
  float kilo_input, orange_input, kilo_final, orange_final, output;
  // Prompt the user to enter the number of kilometers and put that input into kilo_input
  printf("How many kilometers can your ship travel in one day?\n");
  scanf("%f", &kilo_input);
  // Prompt the user to enter the number of crew members and put that input into orange_input
  printf("How many crew members can your ship hold?\n");
  scanf("%f", &orange_input);
  // Divide the travel distance and the number of kilometers per day to get the number of days it takes
  kilo_final = (TRAVEL_DISTANCE / kilo_input);
  // Multiply the number of crew members by the oranges per member to get the total oranges needed in one day
  orange_final = (ORANGES_PER_MEMBER * orange_input);
  // Multiply the number of days by the number of oranges per day
  output = kilo_final * orange_final;
  // Output the total number of oranges
  printf("You will need %.2f oranges to make the trip!\n",output);

  return 0;
}
