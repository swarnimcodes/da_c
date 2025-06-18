#include "da.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  // Initialize array with capacity 2
  DynamicArray *da = da_init(2);
  if (!da) {
    fprintf(stderr, "Allocation failed\n");
    return 1;
  }

  // Push values
  da_push(da, 10);
  da_push(da, 20);
  da_push(da, 30); // Triggers resize to 4

  // Update value
  da_set(da, 1, 25);

  // Pop value
  int64_t val;
  da_pop(da, &val);
  printf("Popped: %ld\n", val); // Output: Popped: 30

  // Get value
  da_get(da, 0, &val);
  printf("First element: %ld\n", val); // Output: First element: 10

  // Shrink to fit
  da_shrink(da);
  printf("Capacity after shrink: %zu\n",
         da->capacity); // Output: Capacity after shrink: 2

  da_destroy(da);
  return 0;
}

// Implementations moved here from da.h
DynamicArray *da_init(size_t initial_capacity) {
  DynamicArray *da = malloc(sizeof(DynamicArray));
  if (!da)
    return NULL;

  da->data = malloc(initial_capacity * sizeof(int64_t));
  if (!da->data && initial_capacity > 0) {
    free(da);
    return NULL;
  }

  da->size = 0;
  da->capacity = initial_capacity;
  return da;
}

void da_destroy(DynamicArray *da) {
  if (da) {
    free(da->data);
    free(da);
  }
}

bool da_resize(DynamicArray *da, size_t new_capacity) {
  if (new_capacity < da->size)
    return false;

  int64_t *new_data = realloc(da->data, new_capacity * sizeof(int64_t));
  if (!new_data && new_capacity > 0)
    return false;

  da->data = new_data;
  da->capacity = new_capacity;
  return true;
}

bool da_push(DynamicArray *da, int64_t value) {
  if (da->size == da->capacity) {
    size_t new_cap = (da->capacity == 0) ? 1 : da->capacity * 2;
    if (!da_resize(da, new_cap))
      return false;
  }

  da->data[da->size++] = value;
  return true;
}

bool da_pop(DynamicArray *da, int64_t *value) {
  if (da->size == 0)
    return false;
  *value = da->data[--da->size];
  return true;
}

bool da_get(DynamicArray *da, size_t index, int64_t *value) {
  if (index >= da->size)
    return false;
  *value = da->data[index];
  return true;
}

bool da_set(DynamicArray *da, size_t index, int64_t value) {
  if (index >= da->size)
    return false;
  da->data[index] = value;
  return true;
}

bool da_shrink(DynamicArray *da) { return da_resize(da, da->size); }
