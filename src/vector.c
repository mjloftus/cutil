#include "../include/vector.h"

Vector* vector_create(size_t elem_size) {
	size_t default_capacity = VECTOR_DEFAULT_CAPACITY;
	Vector* v = malloc(sizeof(Vector));
	if (!v) return NULL;
	v->_size = 0;
	v->_capacity = default_capacity;
	v->_elem_size = elem_size;
	v->_data = malloc(v->_capacity * elem_size);
	if(!v->_data) {
		free(v);
		return NULL;
	}
	return v;
}

void vector_delete(Vector* v) {
	if (!v) return;
	free(v->_data);
	free(v);
}

void* vector_get(Vector* v, size_t i) {
	if (!v) return NULL;
	if (i >= v->_size) return NULL;
	return v->_data + (v->_elem_size * i);
}

size_t vector_in(Vector* v, void* d) {
	if (!v || !d) return -1;
	for (size_t i = 0; i < v->_size; ++i) {
		if (!memcmp(v->_data + (i * v->_elem_size), d, v->_elem_size)) return i;
	}
	return -1;
}

size_t vector_length(Vector* v) {
	if (!v) return -1;
	return v->_size;
}

void* vector_pop(Vector* v) {
	if (!v) return NULL;
	if (v->_size == 0) return NULL;
	--(v->_size);
	return v->_data + (v->_size * v->_elem_size);
}

void vector_push(Vector* v, void* d) {
	memcpy(v->_data + (v->_size * v->_elem_size), d, v->_elem_size);
	++(v->_size);
	if (v->_size == v->_capacity) _vector_increase_capacity(v);
}

void vector_reduce(Vector* v, void(*f)(void*, void*), void* r) {
	for (size_t i = 0; i < vector_length(v); ++i) {
		(*f)(vector_get(v, i), r);
	}
}

void vector_reverse(Vector* v) {
	void* t = malloc(v->_elem_size);
	for (size_t i = 0; i < v->_size / 2; ++i) {
		memcpy(t, v->_data + (i * v->_elem_size), v->_elem_size);
		memcpy(v->_data + (i * v->_elem_size), v->_data + (v->_size - 1 - i) * v->_elem_size, v->_elem_size);
		memcpy(v->_data + (v->_size - 1 - i) * v->_elem_size, t, v->_elem_size);
	}
	free(t);
}

void vector_set(Vector* v, size_t i, void* d) {
	if (!v) return;
	if (i >= v->_size) return;
	memcpy(v->_data + (i * v->_elem_size), d, v->_elem_size);
}

void _vector_increase_capacity(Vector* v) {
	v->_capacity *= 2;
	v->_data = realloc(v->_data, v->_capacity * v->_elem_size);
}

void _vector_decrease_capacity(Vector* v) {
	if (v->_capacity <= VECTOR_DEFAULT_CAPACITY) return;
	if (v->_capacity / 2 < v->_size) return;
	v->_capacity /= 2;
	v->_data = realloc(v->_data, v->_capacity * v->_elem_size);
}
