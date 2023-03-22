#include "../inc/vec.h"
#include <string.h>

t_vec* vec(int capacity) {
    t_vec* vec = (t_vec*)malloc(sizeof(t_vec));
    vec->array = (int*)malloc(capacity * sizeof(int));
    vec->size = 0;
    vec->capacity = capacity;
    return vec;
}

void resize_vec(t_vec* vec) {
    vec->capacity *= 2;
    vec->array = (int*)realloc(vec->array, vec->capacity * sizeof(int));
}

void push_back_vec(t_vec* vec, int value) {
    if (vec->size == vec->capacity) {
        resize_vec(vec);
    }
    vec->array[vec->size++] = value;
}

int size_vec(t_vec* vec) {
    return vec->size;
}

t_vec *vec_from_array(int size, int *data) {
    t_vec *vec = (t_vec*)malloc(sizeof(t_vec));
    vec->array = (int*)malloc(size * sizeof(int));
    vec->size = size;
    vec->capacity = size;
    memcpy(vec->array, data, size * sizeof(int));
    return vec;
}