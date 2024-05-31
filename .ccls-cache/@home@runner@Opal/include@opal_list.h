#ifndef OPAL_LIST_H
#define OPAL_LIST_H

#include "opal.h"

typedef struct STRUCT_OPAL_LIST {
  void **items;
  size_t size;
} OpalList_T;

OpalList_T *init_list_type();
void add_element_list(void *item, OpalList_T* list);
void free_list_type(OpalList_T *list);
#endif