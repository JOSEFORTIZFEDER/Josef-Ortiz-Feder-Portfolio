/*
 * Josef Ortiz-Feder
 * 10/7/2020
 * Program 5 - Setting Sail
*/

#include <stdio.h>

int main()
{
  // Data Dictionary
  //FILE *ifp;
  float cold_temp, hot_temp, curr_temp; //percent_of_days;
  char file_name[30];
  float percent_of_days, curr_best_month;
  int nums, num_days=0, month_to_leave=0;


  // Prompt the user for preferred temperatures
  printf("Tell me about your crew's preferred temperature for sailing:\n");
  printf("What is the coldest temperature they can sail in?\n");
  scanf("%f", &cold_temp);
  printf("What is the hottest temperature they can sail in?\n");
  scanf("%f", &hot_temp);

  // Prompt the user for an array of chars for the file name
  printf("Please enter the name of the weather data file:\n");
  scanf("%s", &file_name);
  printf("\n");

  // Open the file using the file_name
  FILE *ifp = fopen(file_name, "r");

  // For loop that loops through all 12 months
  for(int i=0; i<12; ++i)
  {
    // Reset the number of days and percent for the next month
    num_days = 0;
    percent_of_days = 0;

    // Get the number of values for each month
    fscanf(ifp, " %d", &nums);

    // Iterate the amount of values for a given month
    for(int j=0; j<nums; ++j)
    {
      // Get the temperature
      fscanf(ifp, "%f", &curr_temp);

      // If the temperature fits within given parameters, than add the # of days
      if(curr_temp <= hot_temp && curr_temp >= cold_temp)
      {
        num_days += 1;
      }
    }
    // Calculate the percent of the days that fit within the temperature
    percent_of_days = 100 * ((float)num_days / (float)nums);

    // Print the output
    printf("Month %d: %.1f percent of days in range.\n", i+1, percent_of_days);

    // If statement the determine which month is the best to set sail
    if(percent_of_days > curr_best_month)
    {
      month_to_leave = i+1;
      curr_best_month = percent_of_days;
    }
  }
  // Output the best month
  printf("You should leave for the Caribbean in month %d!\n", month_to_leave);

  // Close the file
  fclose(ifp);

  // Return 0
  return 0;


}
