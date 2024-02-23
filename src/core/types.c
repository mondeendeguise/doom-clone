#include "./types.h"

#include <stdlib.h>

void da_init(Dynamic_Array *arr, size_t size) {
    arr->array = malloc(size * sizeof(int));
    arr->size = 0;
    arr->capacity = size;
}

void da_append(Dynamic_Array *arr, int x) {
    if(arr->size >= arr->capacity) {
        arr->capacity++;
        arr->array = realloc(arr->array, (arr->capacity * sizeof(int)));
    }
    arr->array[arr->size++] = x;
}

void da_deallocate(Dynamic_Array *arr) {
    free(arr->array);
    arr->array = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

