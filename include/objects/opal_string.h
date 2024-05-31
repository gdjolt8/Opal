#ifndef OPAL_STRING_H
#define OPAL_STRING_H

#include "../opal.h"
typedef struct
{
  char *str;
  size_t len;
} OpalString_T;

OpalString_T *new_string_object(char *str);
size_t string_object_length(OpalString_T *str);
#endif