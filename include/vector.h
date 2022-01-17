#ifndef __VECTOR_CUTIL
#define __VECTOR_CUTIL

#include <stdlib.h>
#include <string.h>

const size_t VECTOR_DEFAULT_CAPACITY = 2;

typedef enum _vector_error {
	E_VECTOR_SUCCESS,
	E_VECTOR_INVALID = -1,
	E_VECTOR_NOMEM = -2,
	E_VECTOR_BOUNDS = -3,
	E_VECTOR_NOFOUND = -4
} vector_error_t;

typedef struct Vector {
	void* _data;
/* TODO: enforce max size on vector _size */
	size_t _size;
	size_t _capacity;
	size_t _elem_size;
} Vector;

vector_error_t vector_create(size_t, Vector**);
vector_error_t vector_delete(Vector**);

vector_error_t vector_get(Vector*, size_t, void*);
vector_error_t vector_in(Vector*, void*, size_t*);
vector_error_t vector_length(Vector*, size_t*);
vector_error_t vector_pop(Vector*, void*);
vector_error_t vector_push(Vector*, void*);
vector_error_t vector_reduce(Vector*, void(void*, void*), void*);
vector_error_t vector_reverse(Vector*);
vector_error_t vector_set(Vector*, size_t, void*);

void _vector_decrease_capacity(Vector*);
void _vector_increase_capacity(Vector*);

#endif
