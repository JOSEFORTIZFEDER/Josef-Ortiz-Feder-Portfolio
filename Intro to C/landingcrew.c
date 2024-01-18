/*
 * Josef Ortiz-Feder
 * 9/20/2020
 * Program 4 - Landing Crew
*/

#include <stdio.h>

int main(void)
{
  // Data Dictionary
  int num_of_observed, num_of_trips;
  float trip_length, trip_total, trip_average;

  // Prompt the user for the number of days observed
  printf("How many days will you observe the landing crew?\n");
  scanf("%d", &num_of_observed);

  // For loop that iterates for each day that user entered
  for(int i=0; i<num_of_observed; ++i)
  {
    // Reset the trip total
    trip_total = 0;

    // Prompt the user for the number of trips completed in a day
    printf("\nHow many trips were completed in day #%d?\n", i+1);
    scanf("%d", &num_of_trips);

    // Nested for loop that iterates for the number of trips in a day
    for(int j=0; j<num_of_trips; ++j)
    {
      // Prompt the user for each trip length and add it to the total
      printf("How long was trip #%d?\n", j+1);
      scanf("%f", &trip_length);
      trip_total += trip_length;
    }

    // Take the average trip total and output it to the user
    trip_average = trip_total / num_of_trips;
    printf("Day #%d:", i+1);
    printf(" The average time was %.3f.\n\n", trip_average);
  }

  // Return 0
  return 0;
}
