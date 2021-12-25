#include <check.h>
#include "../vector.h"

/* Test Fixtures */
Vector* good_vector;

void setup_good_vector(void) {
	good_vector = vector_create(sizeof(int));
	for (int i = 0; i < 10; ++i) {
		vector_push(good_vector, &i);
	}
}

void teardown_good_vector(void) {
	vector_delete(good_vector);
}

/* vector_create */
START_TEST (create_returns_vector_when_success) {
	Vector* v = vector_create(4);
	ck_assert_ptr_nonnull(v);
	vector_delete(v);
} END_TEST

/* TODO: mock malloc to simulate failure */

/* vector_get */
START_TEST (get_returns_elem_when_in_range) {
	for (int i = 0; i < 10; ++i) {
		ck_assert_int_eq(*((int*)vector_get(good_vector, i)), i);
	}
} END_TEST


START_TEST (get_returns_null_when_out_of_range) {
	for (int i = 10; i < 20; ++i) {
		ck_assert_ptr_null(vector_get(good_vector, i));
	}
} END_TEST

START_TEST (get_returns_null_when_no_vector) {
	ck_assert_ptr_null(vector_get(NULL, 5));
} END_TEST

/* vector_in */
START_TEST (in_returns_elem_when_found) {
	for (int i = 9; i >= 0; --i) {
		ck_assert_int_eq(vector_in(good_vector, &i), i);
	}
} END_TEST


START_TEST (in_returns_minus_one_when_not_found) {
	for (int i = 10; i < 20; ++i) {
		ck_assert_int_eq(vector_in(good_vector, &i), -1);
	}
} END_TEST

START_TEST (in_returns_minus_one_when_no_vector) {
	int i = 4;
	ck_assert_int_eq(vector_in(NULL, &i), -1);
} END_TEST

START_TEST (in_returns_minus_one_when_no_data) {
	ck_assert_int_eq(vector_in(good_vector, NULL), -1);
} END_TEST

/* vector_length */
START_TEST (length_returns_size_of_vector) {
	ck_assert_int_eq(vector_length(good_vector), 10);
} END_TEST

START_TEST (length_returns_minus_one_when_no_vector) {
	ck_assert_int_eq(vector_length(NULL), -1);
} END_TEST

/* vector_pop */
START_TEST (pop_returns_last_value_of_vector) {
	for (int i = 9; i >= 0; --i) {
		ck_assert_int_eq(*((int*)vector_pop(good_vector)), i);
	}
} END_TEST

START_TEST (pop_removes_element_from_vector) {
	ck_assert_int_eq(vector_length(good_vector), 10);
	for (int i = 0; i < 10; ++i) {
		vector_pop(good_vector);
		ck_assert_int_eq(vector_length(good_vector), 10-i-1);
	}
} END_TEST

START_TEST (pop_returns_null_when_vector_empty) {
	Vector* v = vector_create(sizeof(int));
	ck_assert_ptr_null(vector_pop(v));
} END_TEST

START_TEST (pop_returns_null_when_no_vector) {
	ck_assert_ptr_null(vector_pop(NULL));
} END_TEST

Suite* vector_suite(void) {
	Suite* s;
	s = suite_create("Vector");

	TCase* tc_create;
	tc_create = tcase_create("create");
	tcase_add_test(tc_create, create_returns_vector_when_success);
	suite_add_tcase(s, tc_create);

	TCase* tc_get;
	tc_get = tcase_create("get");
	tcase_add_checked_fixture(tc_get, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_get, get_returns_elem_when_in_range);
	tcase_add_test(tc_get, get_returns_null_when_out_of_range);
	tcase_add_test(tc_get, get_returns_null_when_no_vector);
	suite_add_tcase(s, tc_get);

	TCase* tc_in;
	tc_in = tcase_create("in");
	tcase_add_checked_fixture(tc_in, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_in, in_returns_elem_when_found);
	tcase_add_test(tc_in, in_returns_minus_one_when_not_found);
	tcase_add_test(tc_in, in_returns_minus_one_when_no_vector);
	tcase_add_test(tc_in, in_returns_minus_one_when_no_data);
	suite_add_tcase(s, tc_in);

	TCase* tc_length;
	tc_length = tcase_create("length");
	tcase_add_checked_fixture(tc_length, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_length, length_returns_size_of_vector);
	tcase_add_test(tc_length, length_returns_minus_one_when_no_vector);
	suite_add_tcase(s, tc_length);

	TCase* tc_pop;
	tc_pop = tcase_create("pop");
	tcase_add_checked_fixture(tc_pop, setup_good_vector, teardown_good_vector);
	tcase_add_test(tc_pop, pop_returns_last_value_of_vector);
	tcase_add_test(tc_pop, pop_removes_element_from_vector);
	tcase_add_test(tc_pop, pop_returns_null_when_vector_empty);
	tcase_add_test(tc_pop, pop_returns_null_when_no_vector);
	suite_add_tcase(s, tc_pop);

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
