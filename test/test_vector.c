#include <check.h>
#include "../vector.h"

/*
 * vector_create
 */
START_TEST (create_returns_vector_on_success) {
	Vector* v = vector_create(4);
	ck_assert_ptr_nonnull(v);
	vector_delete(v);
} END_TEST

/*
 * vector_get
 */
START_TEST (get_returns_elem_in_range) {
	Vector* v = vector_create(sizeof(int));
	for (int i = 0; i < 10; ++i) {
		vector_push(v, &i);
	}
	for (int i = 0; i < 10; ++i) {
		ck_assert_int_eq(*((int*)vector_get(v, i)), i);
	}
	vector_delete(v);
} END_TEST


START_TEST (get_returns_null_out_of_range) {
	Vector* v = vector_create(sizeof(int));
	for (int i = 0; i < 10; ++i) {
		vector_push(v, &i);
	}
	for (int i = 10; i < 20; ++i) {
		ck_assert_ptr_null(vector_get(v, i));
	}
	vector_delete(v);
} END_TEST

/*
 * vector_in
 */
START_TEST (in_returns_elem_when_found) {
	Vector* v = vector_create(sizeof(int));
	for (int i = 0; i < 10; ++i) {
		vector_push(v, &i);
	}
	for (int i = 0; i < 10; ++i) {
		ck_assert_int_eq(*((int*)vector_in(v, &i)), i);
	}
	vector_delete(v);
} END_TEST


START_TEST (in_returns_null_when_not_found) {
	Vector* v = vector_create(sizeof(int));
	for (int i = 0; i < 10; ++i) {
		vector_push(v, &i);
	}
	for (int i = 10; i < 20; ++i) {
		ck_assert_ptr_null(vector_in(v, &i));
	}
	vector_delete(v);
} END_TEST

Suite* vector_suite(void) {
	Suite* s;
	TCase* tc_create;
	s = suite_create("Vector");
	tc_create = tcase_create("create");
	tcase_add_test(tc_create, create_returns_vector_on_success);
	suite_add_tcase(s, tc_create);
	TCase* tc_get;
	tc_get = tcase_create("get");
	tcase_add_test(tc_get, get_returns_elem_in_range);
	tcase_add_test(tc_get, get_returns_null_out_of_range);
	suite_add_tcase(s, tc_get);
	TCase* tc_in;
	tc_in = tcase_create("in");
	tcase_add_test(tc_in, in_returns_elem_when_found);
	tcase_add_test(tc_in, in_returns_null_when_not_found);
	suite_add_tcase(s, tc_in);

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
