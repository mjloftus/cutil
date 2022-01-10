#include "../include/vector.h"

vector_error_t vector_create(size_t elem_size, Vector* vector) {
	size_t default_capacity = 2;
	vector = malloc(sizeof(Vector));
	if (!vector) return E_VECTOR_NOMEM;
	vector->_size = 0;
	vector->_capacity = default_capacity;
	vector->_elem_size = elem_size;
	// TODO: test for overflow
	vector->_data = malloc(vector->_capacity * elem_size);
	if(!vector->_data) {
		free(vector);
		return E_VECTOR_NOMEM;
	}
	return E_VECTOR_SUCCESS;
}

vector_error_t vector_delete(Vector* vector) {
	if (!vector) return E_VECTOR_INVALID;
	free(vector->_data);
	free(vector);
	return E_VECTOR_SUCCESS;
}

vector_error_t vector_get(Vector* vector, size_t index, void* data) {
	if (!vector || !data) return E_VECTOR_INVALID;
	if (index >= vector->_size) return E_VECTOR_BOUNDS;
	memcpy(data, vector->_data + (vector->_elem_size * index), vector->_elem_size);
	return E_VECTOR_SUCCESS;
}

vector_error_t vector_in(Vector* vector, void* data, size_t* index) {
	if (!vector || !data || !index) return E_VECTOR_INVALID;
	for (size_t i = 0; i < vector->_size; ++i) {
		if (!memcmp(vector->_data + (i * vector->_elem_size), data, vector->_elem_size)) {
		       	*index = i;
			break;
		}
	}
	return E_VECTOR_SUCCESS;
}

vector_error_t vector_length(Vector* vector, size_t* length) {
	if (!vector || !length) return E_VECTOR_INVALID;
	*length = vector->_size;
	return E_VECTOR_SUCCESS;
}

vector_error_t vector_pop(Vector* vector, void* data) {
	if (!vector || !data) return E_VECTOR_INVALID;
	if (vector->_size == 0) return E_VECTOR_BOUNDS;
	--(vector->_size);
	memcpy(data, vector->_data + (vector->_elem_size * vector->_size), vector->_elem_size);
	return E_VECTOR_SUCCESS;
}

vector_error_t vector_push(Vector* vector, void* data) {
	if (!vector || !data) return E_VECTOR_INVALID;
	memcpy(vector->_data + (vector->_size * vector->_elem_size), data, vector->_elem_size);
	++(vector->_size);
	if (vector->_size == vector->_capacity) _vector_increase_capacity(vector);
	return E_VECTOR_SUCCESS;
}

vector_error_t vector_reduce(Vector* vector, void(*fun)(void*, void*), void* result) {
	if (!vector || !fun || !result) return E_VECTOR_INVALID;
	void* data = malloc(sizeof(vector->_elem_size));
	if (!data) return E_VECTOR_NOMEM;
	for (size_t i = 0; i < vector->_size; ++i) {
		vector_get(vector, i, data);
		(*fun)(data, result);
	}
	free(data);
	return E_VECTOR_SUCCESS;
}

vector_error_t vector_reverse(Vector* vector) {
	if (!vector) return E_VECTOR_INVALID;
	void* data = malloc(vector->_elem_size);
	if (!data) return E_VECTOR_NOMEM;
	for (size_t i = 0; i < vector->_size / 2; ++i) {
		memcpy(data, vector->_data + (i * vector->_elem_size), vector->_elem_size);
		memcpy(vector->_data + (i * vector->_elem_size), vector->_data + (vector->_size - 1 - i) * vector->_elem_size, vector->_elem_size);
		memcpy(vector->_data + (vector->_size - 1 - i) * vector->_elem_size, data, vector->_elem_size);
	}
	free(data);
	return E_VECTOR_SUCCESS;
}

vector_error_t vector_set(Vector* vector, size_t index, void* data) {
	if (!vector || !data) return E_VECTOR_INVALID;
	if (index >= vector->_size) return E_VECTOR_BOUNDS;
	memcpy(vector->_data + (index * vector->_elem_size), data, vector->_elem_size);
	return E_VECTOR_SUCCESS;
}

void _vector_increase_capacity(Vector* vector) {
	vector->_capacity *= 2;
	vector->_data = realloc(vector->_data, vector->_capacity * vector->_elem_size);
}

void _vector_decrease_capacity(Vector* vector) {
	if (vector->_capacity <= 2) return;
	if (vector->_capacity / 2 < vector->_size) return;
	vector->_capacity /= 2;
	vector->_data = realloc(vector->_data, vector->_capacity * vector->_elem_size);
}
