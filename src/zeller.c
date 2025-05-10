/**
 * Implement Celler's Congruence to calculate the day of the week for a given date.
 * Current implementation supports up to 4-dit years: YYYY
 */
#include <stdio.h>
#include <math.h>
#include <string.h>

char* WEEKDAY[7] = {
  "SAT",
  "SUN",
  "MON",
  "TUE",
  "WED",
  "THU",
  "FRI",
};

unsigned int MONTH[12] = {
  3,  // March
  4,  // April
  5,  // May
  6,  // June
  7,  // July
  8,  // August
  9,  // Sempember
  10, // October
  11, // November
  12, // December
  13, // January
  14  // Februrary
};

/**
 *
 * h = (q + floor(13(m+1)/5) + K + floor(K/4) + floor(J/4) - 2J) mod 7
 * Where:

 * - h is the day of the week (0 = Saturday, 1 = Sunday, ..., 6 = Friday)
 * - q is the day of the month
 * - m is the month (3 = March, 4 = April, ..., 14 = February)
 * - Note: January and February are counted as months 13 and 14 of the previous year
 * - K is the year of the century (year % 100)
 * - J is the zero-based century (year/100)
 */
unsigned int zeller(unsigned int q, unsigned int month, unsigned int year)
{
  unsigned int m, K, J;
  m = MONTH[month-3];
  K = year % 100;
  J = year / 100;
  return (unsigned int)(q+floor(13*(m+1)/5)+K+floor(K/4)+floor(J/4)-2*J) % 7;
}

int main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("Usage: ./zeller.out YYYY-MM-DD\n");
    return 1;
  }
  if (strlen(argv[1]) != 10) {
    printf("Invalid date format: %s. Use YYYY-MM-DD\n", argv[1]);
    return 2;
  }
  unsigned int year, month, day, h;
  if (sscanf(argv[1], "%u-%u-%u", &year, &month, &day) != 3) {
    printf("Invalid date format. Use YYYY-MM-DD\n");
    return 3;
  }
  if (year > 9999 || month > 14 || day > 31) {
    printf("Invalid date format %s. Use YYYY-MM-DD\n", argv[1]);
    return 4;
  }
  if (year == 0 || month == 0 || day == 0) {
    printf("Invalid date format %s. Use YYYY-MM-DD\n", argv[1]);
    return 5;
  }

  // adjust month and year if month is Jan or Feb
  if (month < 3) {
    month += 12;
    year -= 1;
  }

  // adjust year to be the preivous if month is Jan or Feb
  h = zeller(day, month, year);

  printf("The day of the week for %s is: %s\n", argv[1], WEEKDAY[h]);
  return 0;
}
