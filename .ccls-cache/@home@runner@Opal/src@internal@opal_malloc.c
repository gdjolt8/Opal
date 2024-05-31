#include "../../include/opal_malloc.h"

OpalList_T* list = NULL;
OpAlloc_T *head = NULL;


void *opal_malloc (size_t nmemb, size_t size) {
    void *ptr = malloc(size * nmemb);
    memset(ptr, 0, size * nmemb);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    OpAlloc_T *new_allocation = (OpAlloc_T *)malloc(sizeof(OpAlloc_T));
    memset(new_allocation, 0, sizeof(OpAlloc_T));
    if (new_allocation == NULL) {
        free(ptr);
        fprintf(stderr, "GC Allocation: Memory allocation failed\n");
        return NULL;
    }
    new_allocation->ptr = ptr;
    new_allocation->size = size;
    new_allocation->next = head;
    head = new_allocation;
    return ptr;
}

void *opal_realloc (void *ptr, size_t size) {
    if (ptr == NULL) {
        return opal_malloc(1, size);
    }
    if (size == 0) {
        opal_gc_free_malloc_ptr(ptr);
        return NULL;
    }
    OpAlloc_T *current = head;
    while (current != NULL) {
        if (current->ptr == ptr) {
            void *new_ptr = realloc(ptr, size);
            if (new_ptr == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                return NULL;
            }
            current->ptr = new_ptr;
            current->size = size;
            return new_ptr;
        }
        current = current->next;
    }
    fprintf(stderr, "Attempt to realloc untracked memory\n");
    return NULL;
}
void opal_gc_free_all()
{
    OpAlloc_T *current = head;
    while (current != NULL) {
        OpAlloc_T *to_free = current;
        current = current->next;
        free(to_free->ptr);
        free(to_free);
    }
    head = NULL;

}
void opal_gc_free_malloc_ptr (void *ptr)
{
    OpAlloc_T **current = &head;
    while (*current != NULL) {
        if ((*current)->ptr == ptr) {
            OpAlloc_T *to_free = *current;
            *current = (*current)->next;
            free(to_free->ptr);
            free(to_free);
            return;
        }
        current = &(*current)->next;
    }
    fprintf(stderr, "Attempt to free untracked memory\n");
    exit(1);
}