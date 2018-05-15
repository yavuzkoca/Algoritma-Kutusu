/*
* Copyright (c) 2018 by Uğur Ali Kaplan
* You are free to do anything you want with this code
* provided you give attribute to original author.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int year, month, day;

  // Get a date from the user
  printf("Enter date [year month day]: ");
  scanf("%d %d %d", &year, &month, &day);

  // Check if the date is valid
  if ((month < 1 || month > 12) ||
      (day < 1 || (month == 2)
           ? day > 28
           : (month == 1 || month == 3 || month == 5 || month == 7 ||
              month == 8 || month == 10 || month == 12)
                 ? day > 31
                 : day > 30)) {
    printf("Invalid date.\n");
    return EXIT_FAILURE;
  }

  // Get an end year
  int end_year;
  printf("Enter end year: ");
  scanf("%d", &end_year);

  // Use Zellar's congruence
  int q, m, j, k;
  q = day;
  m = (month == 1 || month == 2) ? month + 12 : month;
  j = year / 100;
  k = (month == 1 || month == 2) ? ((year % 100) - 1) : (year % 100);

  int mod_result =
      ((q + ((13 * (m + 1)) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7);

  switch (mod_result) {
  // Determine the corresponding days
  case 0:
    printf("It's a Saturday.\n");
    break;
  case 1:
    printf("It's a Sunday.\n");
    break;
  case 2:
    printf("It's a Monday.\n");
    break;
  case 3:
    printf("It's a Tuesday.\n");
    break;
  case 4:
    printf("It's a Wednesday.\n");
    break;
  case 5:
    printf("It's a Thursday.\n");
    break;
  default:
    printf("It's a Friday.\n");
    break;
  }

  int same = 0;

  // Calculate the same day-and-month between years
  for (int i = year + 1; i <= end_year; i++) {
    j = i / 100;
    k = (month == 1 || month == 2) ? ((i % 100) - 1) : (i % 100);
    int new_mod =
        ((q + ((13 * (m + 1)) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7);
    if (new_mod == mod_result) {
      same += 1;
    }
  }

  // Print the result of the calculation
  printf("Same day-and-month on same weekday between %d and %d: %d\n", year + 1,
         end_year, same);

  return EXIT_SUCCESS;
}
