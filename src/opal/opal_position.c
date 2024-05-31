#include "../../include/opal/opal_position.h"

OpalPosition_T *init_opal_position(size_t line, size_t column)
{
  OpalPosition_T *p = opal_malloc(1, sizeof(OpalPosition_T));
  p->line = line;
  p->column = column;
  return p;
}
char *opal_position_to_string(OpalPosition_T *pos)
{
  char *buf = opal_malloc(256, sizeof(char));
  sprintf(buf, "(%zu, %zu)\n", pos->line, pos->column);
  return buf;
}