#include "../include/opal_datetime.h"

Opal_DateTime *new_datetime_object()
{
  Opal_DateTime *datetime = (Opal_DateTime *)opal_malloc(1, sizeof(Opal_DateTime));

  
  time_t rawtime;
  struct tm * timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  
  datetime->years = timeinfo->tm_year + 1900;
  datetime->month = timeinfo->tm_mon + 1;
  datetime->day = timeinfo->tm_mday;
  datetime->hours = timeinfo->tm_hour;
  datetime->minutes = timeinfo->tm_min;
  datetime->seconds = timeinfo->tm_sec;
  datetime->microseconds = rawtime;
  return datetime;
}