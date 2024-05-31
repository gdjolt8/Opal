#ifndef OPAL_DATETIME_H
#define OPAL_DATETIME_H

#include "opal.h"

typedef struct 
{
  int month;
  int day;
  int years;
  int hours;
  int seconds;
  int minutes;
  unsigned long microseconds;
} Opal_DateTime;

Opal_DateTime *new_datetime_object();

#endif
