#ifndef __VECTOR_CUTIL
#define __VECTOR_CUTIL

#include <stdlib.h>
#include <string.h>

typedef struct vector {
	void* _data;
	size_t _size;
	size_t _capacity;
	size_t _elem_size;
} vector;

vector* vector_create(size_t);
void vector_delete(vector*);

void* vector_get(vector*, size_t);
size_t vector_length(vector*);
void* vector_pop(vector*);
void vector_push(vector*, void*);
void vector_set(vector*, size_t, void*);

void _vector_decrease_capacity(vector*);
void _vector_increase_capacity(vector*);

#endif
