/**
 * Implement Doomsday algorithm to calculate the day of the week for a given date.
 * It supports dates between 1800s to 2200s (exclusive)
 */

#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned int month;
  unsigned int day;
} Ref;

Ref references[] = {
  {.month = 2,  .day = 28},
  {.month = 2,  .day = 29},
  {.month = 3,  .day = 7},
  {.month = 4,  .day = 4},
  {.month = 5,  .day = 9},
  {.month = 6,  .day = 6},
  {.month = 7,  .day = 11},
  {.month = 8,  .day = 8},
  {.month = 9,  .day = 5},
  {.month = 10, .day = 10},
  {.month = 11, .day = 7},
  {.month = 12, .day = 12}
};

char* WEEKDAY[7] = {
  "SUNDAY",
  "MONDAY",
  "TUESDAY",
  "WEDNESDAY",
  "THURSDAY",
  "FRIDAY",
  "SATURDAY"
};

#define set_anchor(y, a) \
  do { \
    unsigned int ay = y / 100;  \
    switch(ay) {                \
    case(18): a = 5; break; \
    case(19): a = 3; break; \
    case(20): a = 2; break; \
    case(21): a = 0; break; \
    default: a = -1; \
    } \
  } while(0)

#define is_leap(y) ((y % 100 != 0 && y % 4 == 0) || (y % 100 == 0 && y % 400 == 0))

int main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("Usage: ./doomsday.out YYYY-MM-DD\n");
    return 1;
  }

  if (strlen(argv[1]) != 10) {
    printf("Invalid date format: %s\n", argv[1]);
    return 2;
  }

  unsigned int year,month,day;

  if (sscanf(argv[1], "%u-%u-%u", &year, &month, &day) < 3)  {
    printf("Invalid date format: %s\n", argv[1]);
    return 3;
  }

  unsigned int anchor;
  set_anchor(year, anchor);
  if (anchor < 0) {
    printf("Unsupported century: %u\n", year / 100);
    return 4;
  }
  printf("Anchor is %u and thus %s\n", anchor, WEEKDAY[anchor]);

  unsigned int lt = year % 100;
  unsigned int ltq = lt / 12;
  unsigned int ltr = lt % 12;
  unsigned int doomsday = (ltq + ltr + (ltr / 4) + anchor) % 7;
  printf("Doomsday is WEEKDAY[%u]: %s\n", doomsday, WEEKDAY[doomsday]);
  printf("ltq = %u, ltr = %u, doomsday = %u, anchor = %u\n", ltq, ltr, doomsday, anchor);

  Ref ref;
  int found_ref = 0;
  if (is_leap(year) && month == 2) {
    ref = references[1];
    found_ref = 1;
  } else if (month == 2) {
    ref = references[0];
    found_ref = 1;
  } else {
    for (size_t i = 2; i < 12; i++) {
      if (references[i].month == month) {
        ref = references[i];
        found_ref = 1;
        break;
      }
    }
  }

  if (!found_ref) {
    printf("No reference day found for month %u\n", month);
    return 5;
  }
  printf("Reference day is %u-%u\n", ref.month, ref.day);

  // Use signed int to handle negative shifts
  int shift = (int)day - (int)ref.day;
  printf("Need to shift reference day by %d days\n", shift);

  // Calculate the new weekday by adding the shift to the doomsday
  // and taking modulo 7. For negative shifts, add 7 before modulo
  int weekday = ((int)doomsday + shift) % 7;
  while (weekday < 0) weekday += 7;

  printf("The week day for %s is %s\n", argv[1], WEEKDAY[weekday]);

  return 0;

}
