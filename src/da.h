#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  int64_t *data;
  size_t size;
  size_t capacity;
} DynamicArray;

// Function declarations
DynamicArray *da_init(size_t initial_capacity);
void da_destroy(DynamicArray *da);
bool da_resize(DynamicArray *da, size_t new_capacity);
bool da_push(DynamicArray *da, int64_t value);
bool da_pop(DynamicArray *da, int64_t *value);
bool da_get(DynamicArray *da, size_t index, int64_t *value);
bool da_set(DynamicArray *da, size_t index, int64_t value);
bool da_shrink(DynamicArray *da);

#endif
