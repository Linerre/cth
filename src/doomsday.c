/**
 * Implement Doomsday algorithm to calculate the day of the week for a given date.
 * It supports dates between 1800s to 2200s (exclusive)
 */

#include <stdio.h>
#include <math.h>
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

#define set_anchor(y, ret) \
  do { \
    unsigned int ay = y / 100;  \
    switch(ay) {                \
    case(18): ret = 5; break; \
    case(19): ret = 3; break; \
    case(20): ret = 2; break; \
    case(21): ret = 0; break; \
    default: ret = -1; \
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

  unsigned int shift;
  set_anchor(year, shift);
  if (shift < 0) {
    printf("Unsupported century: %u", year / 100);
    return 4;
  }

  unsigned int lt = year % 100;
  unsigned int ltq = lt / 12;
  unsigned int ltr = lt % 12;
  unsigned int ret = (ltq + ltr + (ltr / 4) + shift) % 7;
  printf("ltq = %u, ltr = %u, ret = %u, shift = %u\n", ltq, ltr, ret, shift);

  Ref ref;
  if (is_leap(year) && month == 2) ref = references[1];
  else if (month == 2) ref = references[0];
  else
    for (size_t i = 2; i < 11; i++)
      if (references[i].month == month) {
        ref = references[i];
        break;
      }
  printf("Reference day is %u-%u\n", ref.month, ref.day);

  unsigned int idx = ref.day > ret ? ref.day - ret : ret - ref.day;
  if (idx > 6) {
    printf("Invalid doomsday: %u", ret);
    return 5;
  }
  printf("The week day for %s is %s\n", argv[1], WEEKDAY[idx]);

  return 0;

}
