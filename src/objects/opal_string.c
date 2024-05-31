#include "../../include/opal.h"

OpalString_T *new_string_object(char *str)
{
  OpalString_T *s = opal_malloc(1, sizeof(OpalString_T));
  s->str = str;
  s->len = strlen(str);
  return s;
}

size_t string_object_length(OpalString_T *str)
{
  assert(str != NULL);
  if (str->len != strlen(str->str))
  {
    return strlen(str->str);
  }
  return str->len;
}