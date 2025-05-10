/**
 * Implement Celler's Congruence to calculate the day of the week for a given date.
 */
#include <stdio.h>
#include <math.h>

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
 * Note: January and February are counted as months 13 and 14 of the previous year
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

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: ./zeller.out YYYY-MM-DD\n");
    return 1;
  }
  unsigned int year, month, day, zm, h;
  if (sscanf(argv[1], "%u-%u-%u", &year, &month, &day) != 3) {
    printf("Invalid date format. Use YYYY-MM-DD\n");
    return 2;
  }
  // adjust month
  if (month == 1) zm = 13;
  else if (month == 2) zm = 14;
  else zm = month;

  h = zeller(day, zm, year - (month < 3));

  printf("The day of the week for %s is: %s\n", argv[1], WEEKDAY[h]);
  return 0;
}
