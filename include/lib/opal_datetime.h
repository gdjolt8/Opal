#ifndef OPAL_DATETIME_H
#define OPAL_DATETIME_H

#include "../opal.h"

#define SECS_IN_YEAR 31557600
#define SECS_IN_DAY 86400
#define SECS_IN_HOUR 3600
#define SECS_IN_MIN 60
#define DAYS_IN_YEAR 365
#define DAYS_IN_MONTH 31
#define DAYS_IN_LEAP_YEAR 366
#define MONTHS_IN_YEAR 12
typedef struct 
{
  int month;
  int day;
  int years;
  int hours;
  int seconds;
  int minutes;
  unsigned long microseconds;
  unsigned long unix_time_epoch;
  struct tm* time_object;
} Opal_DateTime;

Opal_DateTime *new_opal_datetime_object();
void opal_datetime_update(Opal_DateTime **datetime);
void opal_datetime_add_n_seconds(Opal_DateTime* datetime, long seconds);
void opal_datetime_add_n_years(Opal_DateTime* datetime, long years);
void opal_datetime_set_unix_seconds(Opal_DateTime* datetime, long seconds);
char *opal_datetime_to_string(Opal_DateTime *datetime);
#endif
