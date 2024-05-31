#ifndef OPAL_ERROR_H
#define OPAL_ERROR_H

#include "../opal_list.h"
#include "opal_position.h"
typedef struct
{
  char *err_msg;
  struct STRUCT_OPAL_POSITION *pos;
  const char *directory;
  enum {
    OPAL_ERR_TYPE_ERROR,
    OPAL_ERR_TYPE_WARNING
  } err_type;
  enum {
    OPAL_ERR_SYNTAX,
    OPAL_ERR_SEMANTIC,
    OPAL_ERR_RUNTIME
  } err_level;

} OpalError_T;

OpalError_T *init_opal_error(char *msg, struct STRUCT_OPAL_POSITION *pos, const char* directory, int err_type, int err_level);
void opal_add_error(OpalError_T *err, struct STRUCT_OPAL_LIST* list);
char *opal_error_to_string(OpalError_T *err);
void throw_opal_error(OpalError_T* err);
#endif