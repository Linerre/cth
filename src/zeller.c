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
  "TUR",
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

 * h is the day of the week (0 = Saturday, 1 = Sunday, ..., 6 = Friday)
 * q is the day of the month
 * m is the month (3 = March, 4 = April, ..., 14 = February) (Note: January and February are counted as months 13 and 14 of the previous year)
 * K is the year of the century (year % 100)
 * J is the zero-based century (year/100)
 */
int main(int argc, char* argv[]) {
  unsigned int h, q, m, K, J;
  q = 10;
  m = MONTH[5-3];
  K = 2025 % 100;
  J = 2025 / 100;
  h = (unsigned int)(q + floor(13*(m+1)/5) + K + floor(K/4) + floor(J/4) - 2*J) % 7;

  printf("The day of the week for 2025-05-10 is %s\n", WEEKDAY[h]);
}
