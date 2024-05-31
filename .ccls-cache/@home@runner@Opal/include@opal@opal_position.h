#ifndef OPAL_POSITION_H
#define OPAL_POSITION_H

#include "../opal.h"
typedef struct STRUCT_OPAL_POSITION
{
  size_t line;
  size_t column;
} OpalPosition_T;

OpalPosition_T *init_opal_position(size_t line, size_t column);
char *opal_position_to_string(OpalPosition_T *pos);
#endif
