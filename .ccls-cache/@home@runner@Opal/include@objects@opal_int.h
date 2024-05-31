#ifndef OPAL_INT_H
#define OPAL_INT_H

#include "../opal.h"
typedef struct
{
  bool is_unsigned;
  long long n_value;
  unsigned long long u_value;
} OpalInteger_T;

OpalInteger_T* new_integer_object(bool is_unsigned, long long n_value);
char *integer_object_to_string(OpalInteger_T *integer);
#endif