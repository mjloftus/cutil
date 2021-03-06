#include <check.h>
#include <stdio.h>
#include "../include/vector.h"

/* Test Fixtures */
Vector* good_vector;

void setup_good_vector(void) {
	vector_error_t rc = vector_create(sizeof(int), &good_vector);
	ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
	for (int i = 0; i < 10; ++i) {
		vector_push(good_vector, &i);
	}
}

void teardown_good_vector(void) {
	vector_delete(&good_vector);
}

/* vector_create */
START_TEST (create_inits_vector_when_success) {
	Vector* v = NULL;
	vector_error_t rc = vector_create(4, &v);
	ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
	ck_assert_ptr_nonnull(v);
	vector_delete(&v);
} END_TEST

/* TODO: mock malloc to simulate failure */

/* vector_delete */
START_TEST (delete_frees_vector_when_success) {
	vector_error_t rc = vector_delete(&good_vector);
	ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
	ck_assert_ptr_null(good_vector);
} END_TEST

START_TEST (delete_returns_invalid_error_when_bad_arg) {
	vector_error_t rc = vector_delete(NULL);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	Vector* v = NULL;
	rc = vector_delete(&v);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);
} END_TEST;

/* vector_get */
START_TEST (get_provides_elem_when_success) {
	int* data = malloc(sizeof(int));
	for (int i = 0; i < 10; ++i) {
		vector_error_t rc = vector_get(good_vector, i, data);
		ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
		ck_assert_int_eq(*data, i);
	}
	free(data);
} END_TEST

START_TEST (get_returns_invalid_error_when_bad_arg) {
	vector_error_t rc = vector_get(good_vector, 0, NULL);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	int* data = malloc(sizeof(int));
	rc = vector_get(NULL, 0, data);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);
	free(data);
} END_TEST

START_TEST (get_returns_bounds_error_when_index_out_of_range) {
	int* data = malloc(sizeof(int));
	for (int i = 10; i < 20; ++i) {
		vector_error_t rc = vector_get(good_vector, i, data);
		ck_assert_int_eq(rc, E_VECTOR_BOUNDS);
	}
	free(data);
} END_TEST

/* vector_in */
START_TEST (in_provides_index_when_found) {
	size_t* index = malloc(sizeof(size_t));
	for (int i = 9; i >= 0; --i) {
		vector_error_t rc = vector_in(good_vector, &i, index);
		ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
		ck_assert_int_eq(*index, i);
	}
	free(index);
} END_TEST

START_TEST (in_returns_invalid_error_when_bad_arg) {
	int* data = malloc(sizeof(int));
	size_t* index = malloc(sizeof(size_t));

	vector_error_t rc = vector_in(NULL, data, index);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	rc = vector_in(good_vector, NULL, index);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	rc = vector_in(good_vector, data, NULL);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	free(data);
	free(index);
} END_TEST

START_TEST (in_returns_nofound_error_when_not_found) {
	size_t* index = malloc(sizeof(size_t));
	for (int i = 10; i < 20; ++i) {
		vector_error_t rc = vector_in(good_vector, &i, index);
		ck_assert_int_eq(rc, E_VECTOR_NOFOUND);
	}
	free(index);
} END_TEST

/* vector_length */
START_TEST (length_provides_size_of_vector_when_success) {
	size_t* length = malloc(sizeof(size_t));
	vector_error_t rc = vector_length(good_vector, length);
	ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
	ck_assert_int_eq(*length, 10);
} END_TEST

START_TEST (length_returns_invalid_error_when_bad_arg) {
	size_t* length = malloc(sizeof(size_t));

	vector_error_t rc = vector_length(NULL, length);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	rc = vector_length(good_vector, NULL);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	free(length);
} END_TEST

/* vector_pop */
START_TEST (pop_provides_last_value_of_vector_when_success) {
	int* data = malloc(sizeof(int));
	for (int i = 9; i >= 0; --i) {
		vector_error_t rc = vector_pop(good_vector, data);
		ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
		ck_assert_int_eq(*data, i);
	}
	free(data);
} END_TEST

START_TEST (pop_removes_last_element_from_vector_when_success) {
	int* data = malloc(sizeof(int));
	ck_assert_int_eq(good_vector->_size, 10);
	for (int i = 0; i < 10; ++i) {
		vector_error_t rc = vector_pop(good_vector, data);
		ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
		ck_assert_int_eq(good_vector->_size, 10-i-1);
	}
	free(data);
} END_TEST

START_TEST (pop_returns_invalid_error_when_bad_arg) {
	int* data = malloc(sizeof(int));

	vector_error_t rc = vector_pop(NULL, data);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	rc = vector_pop(good_vector, NULL);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	free(data);
} END_TEST

START_TEST (pop_returns_bounds_error_when_vector_empty) {
	Vector* v;
	vector_create(sizeof(int), &v);
	int* data = malloc(sizeof(int));
	vector_error_t rc = vector_pop(v, data);
	ck_assert_int_eq(rc, E_VECTOR_BOUNDS);
	free(v);
	free(data);
} END_TEST

/* vector_push */
START_TEST (push_adds_value_to_end_of_vector_when_success) {
	int x = 100;
	size_t old_size = good_vector->_size;
	vector_error_t rc = vector_push(good_vector, &x);
	ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
	ck_assert_int_eq(good_vector->_size, old_size + 1);
	int last_element;
	vector_get(good_vector, old_size, &last_element);
	ck_assert_int_eq(last_element, 100);
} END_TEST

START_TEST (push_returns_invalid_error_when_bad_arg) {
	int data = 5;

	vector_error_t rc = vector_push(NULL, &data);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	rc = vector_push(good_vector, NULL);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);
} END_TEST

/* vector_reduce */
START_TEST (reduce_sets_result_according_to_function_when_success) {
	void sum(void* a, void* b) {
		*((int*)b) += *((int*)a);
	}
	void (*f)(void*, void*) = &sum;
	int* result = malloc(sizeof(int));
	*result = 0;
	vector_error_t rc = vector_reduce(good_vector, f, result);
	ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
	ck_assert_int_eq(*result, 45);
	free(result);
} END_TEST

START_TEST (reduce_returns_invalid_error_when_bad_arg) {
	void sum(void* a, void* b) {
		*((int*)b) += *((int*)a);
	}
	void (*f)(void*, void*) = &sum;
	int* result = malloc(sizeof(int));

	vector_error_t rc = vector_reduce(NULL, f, result);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	rc = vector_reduce(good_vector, NULL, result);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	rc = vector_reduce(good_vector, f, NULL);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);

	free(result);
} END_TEST

// TODO: mock malloc to test for nomem error

/* vector_reverse */
START_TEST (reverse_reverses_ordering_of_elements_when_success) {
	vector_error_t rc = vector_reverse(good_vector);
	ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
	int data;
	size_t length;
	vector_length(good_vector, &length);
	for (int i = 0; i < good_vector->_size; ++i) {
		vector_get(good_vector, i, &data);
		ck_assert_int_eq(data, length - 1 - i);
	}
} END_TEST

START_TEST (reverse_returns_invalid_error_when_bad_arg) {
	vector_error_t rc = vector_reverse(NULL);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);
} END_TEST

/* vector_set */
START_TEST (set_sets_offset_location_to_value_when_success) {
	for (int i = 0; i < good_vector->_size; ++i) {
		int k = i + 100;
		vector_error_t rc = vector_set(good_vector, i, &k);
		ck_assert_int_eq(rc, E_VECTOR_SUCCESS);
	}
	for (int i = 0; i < good_vector->_size; ++i) {
		int data;
		vector_get(good_vector, i, &data);
		ck_assert_int_eq(data, i + 100);
	}
} END_TEST

START_TEST (set_returns_invalid_error_when_bad_arg) {
	size_t index = 0;
	int data;

	vector_error_t rc = vector_set(NULL, index, &data);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);
	
	rc = vector_set(good_vector, index, NULL);
	ck_assert_int_eq(rc, E_VECTOR_INVALID);
} END_TEST

START_TEST (set_returns_bounds_error_when_index_out_of_range) {
	int data;
	vector_error_t rc = vector_get(good_vector, good_vector->_size + 1, &data);
	ck_assert_int_eq(rc, E_VECTOR_BOUNDS);
} END_TEST

/* _vector_increase_capacity */
START_TEST (increase_capacity_doubles_capacity_of_vector) {
	Vector* v;
	vector_create(sizeof(int), &v);
	int expected = 2;
	ck_assert_int_eq(v->_capacity, expected);
	for (int i = 0; i < 10; ++i) {
		_vector_increase_capacity(v);
		expected *= 2;
		ck_assert_int_eq(v->_capacity, expected);
	}
} END_TEST

/* _vector_decrease_capacity */
START_TEST (decrease_capacity_halves_capacity_of_vector) {
	Vector* v;
	vector_create(sizeof(int), &v);
	v->_capacity = 2048;
	v->_data = realloc(v->_data, v->_capacity * v->_elem_size);
	int expected = v->_capacity;
	for (int i = 0; i < 10; ++i) {
		_vector_decrease_capacity(v);
		expected /= 2;
		ck_assert_int_eq(v->_capacity, expected);
	}
} END_TEST

START_TEST (decrease_capacity_does_not_reduce_capacity_below_minimum) {
	Vector* v;
	vector_create(sizeof(int), &v);
	ck_assert_int_eq(v->_capacity, 2);
	_vector_decrease_capacity(v);
	ck_assert_int_eq(v->_capacity, 2);
} END_TEST

/* suite */
Suite* vector_suite(void) {
	Suite* s;
	s = suite_create("Vector");

	TCase* tc_create;
	tc_create = tcase_create("create");
	tcase_add_test(tc_create, create_inits_vector_when_success);
	suite_add_tcase(s, tc_create);

	TCase* tc_delete;
	tc_delete = tcase_create("delete");
	tcase_add_checked_fixture(tc_delete, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_delete, delete_frees_vector_when_success);
	tcase_add_test(tc_delete, delete_returns_invalid_error_when_bad_arg);
	suite_add_tcase(s, tc_delete);

	TCase* tc_get;
	tc_get = tcase_create("get");
	tcase_add_checked_fixture(tc_get, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_get, get_provides_elem_when_success);
	tcase_add_test(tc_get, get_returns_invalid_error_when_bad_arg);
	tcase_add_test(tc_get, get_returns_bounds_error_when_index_out_of_range);
	suite_add_tcase(s, tc_get);

	TCase* tc_in;
	tc_in = tcase_create("in");
	tcase_add_checked_fixture(tc_in, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_in, in_provides_index_when_found);
	tcase_add_test(tc_in, in_returns_invalid_error_when_bad_arg);
	tcase_add_test(tc_in, in_returns_nofound_error_when_not_found);
	suite_add_tcase(s, tc_in);

	TCase* tc_length;
	tc_length = tcase_create("length");
	tcase_add_checked_fixture(tc_length, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_length, length_provides_size_of_vector_when_success);
	tcase_add_test(tc_length, length_returns_invalid_error_when_bad_arg);
	suite_add_tcase(s, tc_length);

	TCase* tc_pop;
	tc_pop = tcase_create("pop");
	tcase_add_checked_fixture(tc_pop, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_pop, pop_provides_last_value_of_vector_when_success);
	tcase_add_test(tc_pop, pop_removes_last_element_from_vector_when_success);
	tcase_add_test(tc_pop, pop_returns_invalid_error_when_bad_arg);
	tcase_add_test(tc_pop, pop_returns_bounds_error_when_vector_empty);
	suite_add_tcase(s, tc_pop);

	TCase* tc_push;
	tc_push = tcase_create("push");
	tcase_add_checked_fixture(tc_push, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_push, push_adds_value_to_end_of_vector_when_success);
	tcase_add_test(tc_push, push_returns_invalid_error_when_bad_arg);
	suite_add_tcase(s, tc_push);

	TCase* tc_reduce;
	tc_reduce = tcase_create("reduce");
	tcase_add_checked_fixture(tc_reduce, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_reduce, reduce_sets_result_according_to_function_when_success);
	tcase_add_test(tc_reduce, reduce_returns_invalid_error_when_bad_arg);
	suite_add_tcase(s, tc_reduce);

	TCase* tc_reverse;
	tc_reverse = tcase_create("reverse");
	tcase_add_checked_fixture(tc_reverse, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_reverse, reverse_reverses_ordering_of_elements_when_success);
	tcase_add_test(tc_reverse, reverse_returns_invalid_error_when_bad_arg);
	suite_add_tcase(s, tc_reverse);

	TCase* tc_set;
	tc_set = tcase_create("set");
	tcase_add_checked_fixture(tc_set, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_set, set_sets_offset_location_to_value_when_success);
	tcase_add_test(tc_set, set_returns_invalid_error_when_bad_arg);
	tcase_add_test(tc_set, set_returns_bounds_error_when_index_out_of_range);
	suite_add_tcase(s, tc_set);

	TCase* tc_increase_capacity;
	tc_increase_capacity = tcase_create("_increase_capacity");
	tcase_add_test(tc_increase_capacity, increase_capacity_doubles_capacity_of_vector);
	suite_add_tcase(s, tc_increase_capacity);

	TCase* tc_decrease_capacity;
	tc_decrease_capacity = tcase_create("_decrease_capacity");
	tcase_add_test(tc_decrease_capacity, decrease_capacity_halves_capacity_of_vector);
	tcase_add_test(tc_decrease_capacity, decrease_capacity_does_not_reduce_capacity_below_minimum);
	suite_add_tcase(s, tc_decrease_capacity);

	return s;
}

int main(void) {
	int number_failed;
	Suite* s;
	SRunner* sr;
	s = vector_suite();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
