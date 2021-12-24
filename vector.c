#include "vector.h"

Vector* vector_create(int s) {
	if (s <= 0) return NULL;
	Vector* v = malloc(sizeof(Vector));
	v->_size = 0;
	v->_capacity = 2;
	v->_elem_size = s;
	v->_data = malloc(v->_capacity * s);
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

void* vector_in(Vector* v, void* d) {
	for (size_t i = 0; i < v->_size; ++i) {
		if (!memcmp(v->_data + (i * v->_elem_size), d, v->_elem_size)) return v->_data + (i * v->_elem_size);
	}
	return NULL;
}

size_t vector_length(Vector* v) {
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
	if (v->_capacity <= 2) return;
	if (v->_capacity / 2 < v->_size) return;
	v->_capacity /= 2;
	v->_data = realloc(v->_data, v->_capacity * v->_elem_size);
}
