#include "vector.h"

vector* vector_create(size_t s) {
	vector* v = malloc(sizeof(vector));
	v->_size = 0;
	v->_capacity = 2;
	v->_elem_size = s;
	v->_data = malloc(v->_capacity * s);
	return v;
}

void vector_delete(vector* v) {
	if (!v) return;
	free(v->_data);
	free(v);
}

void* vector_get(vector* v, size_t i) {
	if (!v) return NULL;
	if (i >= v->_size) return NULL;
	return v->_data + (v->_elem_size * i);
}

size_t vector_length(vector* v) {
	return v->_size;
}

void* vector_pop(vector* v) {
	if (!v) return NULL;
	if (v->_size == 0) return NULL;
	--(v->_size);
	return v->_data + (v->_size * v->_elem_size);
}

void vector_push(vector* v, void* x) {
	memcpy(v->_data + (v->_size * v->_elem_size), x, v->_elem_size);
	++(v->_size);
	if (v->_size == v->_capacity) _vector_increase_capacity(v);
}

void vector_set(vector* v, size_t i, void* d) {
	if (!v) return;
	if (i >= v->_size) return;
	memcpy(v->_data + (i * v->_elem_size), d, v->_elem_size);
}

void _vector_increase_capacity(vector* v) {
	v->_capacity *= 2;
	v->_data = realloc(v->_data, v->_capacity * v->_elem_size);
}

void _vector_decrease_capacity(vector* v) {
	if (v->_capacity <= 2) return;
	if (v->_capacity / 2 < v->_size) return;
	v->_capacity /= 2;
	v->_data = realloc(v->_data, v->_capacity * v->_elem_size);
}

/*int main(int argc, char* argv[]) {
	vector* v = vector_create(sizeof(int));
	int x = 2;
	vector_push(v, &x);
	x = 4;
	vector_push(v, &x);
	x = 6;
	vector_push(v, &x);
	x = 8;
	vector_push(v, &x);
	printf("%d, %d\n", *((int*)vector_get(v, 0)), *((int*)vector_get(v, 1)));
	x = 16;
	vector_set(v, 1, &x);
	printf("%d, %d\n", *((int*)vector_get(v, 0)), *((int*)vector_get(v, 1)));
	int a = *((int*)vector_pop(v));
	int b = *((int*)vector_pop(v));
	printf("%d, %d\n", a, b);
	return 0;
} */
