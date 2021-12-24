#ifndef __VECTOR_CUTIL
#define __VECTOR_CUTIL

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector {
	void* _data;
	size_t _size;
	size_t _capacity;
	size_t _elem_size;
} Vector;

Vector* vector_create(size_t);
void vector_delete(Vector*);

void* vector_get(Vector*, size_t);
void* vector_in(Vector*, void*);
size_t vector_length(Vector*);
void* vector_pop(Vector*);
void vector_push(Vector*, void*);
void vector_reverse(Vector*);
void vector_set(Vector*, size_t, void*);

void _vector_decrease_capacity(Vector*);
void _vector_increase_capacity(Vector*);

#endif
