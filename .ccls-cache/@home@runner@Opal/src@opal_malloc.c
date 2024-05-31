#include "../include/opal_malloc.h"

void *opal_malloc (size_t nmemb, size_t size) {
  void *Ptr = malloc(nmemb * size);
  if (!Ptr)
  {
    printf("opal_malloc: memory allocation failed failed\n");
    exit(1);
  }
  memset(Ptr, 0, size * nmemb);
  return Ptr;
}

void free_malloc (void *ptr)
{
  if (!ptr) return;
  free (ptr);
}