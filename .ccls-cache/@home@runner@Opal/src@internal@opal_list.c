#include "../../include/opal_list.h"

OpalList_T *init_list_type() {
  OpalList_T *list = (OpalList_T *)opal_malloc(1, sizeof(OpalList_T));

  list->items = 0;
  list->size = 0;

  return list;
}
void add_element_list(void *item, OpalList_T* list) {
  if (!list) return;
  list->size++;

  if (list->items == NULL)
    list->items = opal_malloc(1, sizeof(void *));
  else
    list->items = opal_realloc(list->items, (list->size *sizeof(void*)));
  list->items[list->size-1] = item;
}
void free_list_type(OpalList_T *list) {
  assert(list);
  for (int i = 0; i < list->size; i++) {
    opal_gc_free_malloc_ptr(list->items[i]);
  }
    opal_gc_free_malloc_ptr(list->items);
  opal_gc_free_malloc_ptr(list);
}