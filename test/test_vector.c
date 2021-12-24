#include <check.h>
#include "../vector.h"

START_TEST (vector_is_created_with_positive_elem_size) {
	Vector* v = vector_create(4);
	ck_assert_ptr_nonnull(v);
	vector_delete(v);
} END_TEST

START_TEST (vector_is_not_created_with_zero_elem_size) {
	Vector* v = vector_create(0);
	ck_assert_ptr_null(v);
	vector_delete(v);
} END_TEST

START_TEST (vector_is_not_created_with_negative_elem_size) {
	Vector* v = vector_create(-1);
	ck_assert_ptr_null(v);
	vector_delete(v);
} END_TEST

Suite* vector_suite(void) {
	Suite* s;
	TCase* tc_create;
	s = suite_create("Vector");
	tc_create = tcase_create("create");
	tcase_add_test(tc_create, vector_is_created_with_positive_elem_size);
	tcase_add_test(tc_create, vector_is_not_created_with_zero_elem_size);
	tcase_add_test(tc_create, vector_is_not_created_with_negative_elem_size);
	suite_add_tcase(s, tc_create);

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
