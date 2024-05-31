#ifndef OPAL_MALLOC_H
#define OPAL_MALLOC_H

#include "opal.h"

typedef struct STRUCT_OPALLOC {
    void *ptr;
    size_t size;
    struct STRUCT_OPALLOC *next;
} OpAlloc_T;


void *opal_malloc (size_t nmemb, size_t size);
void *opal_realloc (void *ptr, size_t size);
void opal_gc_free_malloc_ptr (void *ptr);
void opal_gc_free_all ();
#endif