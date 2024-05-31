#include "../../include/opal/opal_error.h"

OpalError_T *init_opal_error(char *msg, OpalPosition_T *pos, const char *directory, int err_type, int err_level) {
  OpalError_T *err = (OpalError_T *)opal_malloc(1, sizeof(OpalError_T));
  err->err_msg = msg;
  err->pos = pos;
  err->directory = directory;
  err->err_type = err_type;
  err->err_level = err_level;
  return err;
}

void opal_add_error(OpalError_T *err, OpalList_T* list) {
  add_element_list(err, list);
}
char *opal_error_to_string(OpalError_T *err)
{
  char *buf = opal_malloc(1024, sizeof(char));
  sprintf(buf, "%s:%zu:%zu - syntax error: %s", err->directory, err->pos->line + 1, err->pos->column + 1, err->err_msg);
  return buf;
}

void throw_opal_error(OpalError_T* err)
{
  printf("%s\n", opal_error_to_string(err));
  exit(1);
}