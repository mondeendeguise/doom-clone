#pragma once

#include <stddef.h>

typedef struct {
    int *array;
    size_t size;
    size_t capacity;
} Dynamic_Array;

void da_init(Dynamic_Array *arr, size_t size);
void da_append(Dynamic_Array *arr, int x);
void da_deallocate(Dynamic_Array *arr);
