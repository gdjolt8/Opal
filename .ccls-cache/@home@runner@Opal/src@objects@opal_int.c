#include "../../include/objects/opal_int.h"

OpalInteger_T* new_integer_object(bool is_unsigned, long long n_value)
{
  OpalInteger_T *integer = (OpalInteger_T *)opal_malloc(1, sizeof(OpalInteger_T));
  integer->is_unsigned = is_unsigned;
  if (!is_unsigned)
    integer->n_value = n_value;
  else
    integer->u_value = (unsigned long long)n_value;
  return integer;
}
char *integer_object_to_string(OpalInteger_T *integer)
{
  char *i = opal_malloc(128, sizeof(char));
  if (integer->is_unsigned) {
    sprintf(i, "%llu", integer->u_value);
  } else {
    sprintf(i, "%lld", integer->n_value);
  }
  return i;
}