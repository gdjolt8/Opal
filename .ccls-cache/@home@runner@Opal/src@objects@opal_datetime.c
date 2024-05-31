#include "../../include/lib/opal_datetime.h"

Opal_DateTime *new_opal_datetime_object()
{
  Opal_DateTime *datetime = (Opal_DateTime *)opal_malloc(1, sizeof(Opal_DateTime));

  
  time_t rawtime;
  struct tm * timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  datetime->unix_time_epoch = (unsigned long long)rawtime;

  datetime->time_object = timeinfo;
  
  datetime->years = timeinfo->tm_year + 1900;
  datetime->month = timeinfo->tm_mon + 1;
  datetime->day = timeinfo->tm_mday;
  datetime->hours = timeinfo->tm_hour;
  datetime->minutes = timeinfo->tm_min;
  datetime->seconds = timeinfo->tm_sec;
  datetime->microseconds = rawtime;
  return datetime;
}

void opal_datetime_update(Opal_DateTime **datetime) 
{
  *datetime = new_opal_datetime_object();
}

void opal_datetime_add_n_seconds(Opal_DateTime* datetime, long seconds)
{
  opal_datetime_set_unix_seconds(datetime, datetime->unix_time_epoch + seconds);
}

void opal_datetime_set_unix_seconds(Opal_DateTime* datetime, long seconds)
{
  time_t rawtime = seconds;
  struct tm * timeinfo;

  timeinfo = localtime(&rawtime);
  datetime->unix_time_epoch = (unsigned long long)rawtime;

  datetime->time_object = timeinfo;

  datetime->years = timeinfo->tm_year + 1900;
  datetime->month = timeinfo->tm_mon + 1;
  datetime->day = timeinfo->tm_mday;
  datetime->hours = timeinfo->tm_hour;
  datetime->minutes = timeinfo->tm_min;
  datetime->seconds = timeinfo->tm_sec;
  datetime->microseconds = rawtime;
}
void opal_datetime_add_n_years(Opal_DateTime* datetime, long years) {
  opal_datetime_add_n_seconds(datetime, (SECS_IN_YEAR*years));
}
char *opal_datetime_to_string(Opal_DateTime *datetime)
{
  char *n = opal_malloc(1000, sizeof(char));
  strftime(n, 1000*sizeof(char), "%m/%d/%Y, %H:%M:%S", datetime->time_object);
  return n;
}