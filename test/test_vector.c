#include <check.h>
#include "../vector.h"

START_TEST (test_vector_create) {
	vector* v = malloc(sizeof(vector));
	ck_assert_ptr_nonnull(v);
} END_TEST

Suite* vector_suite(void) {
	Suite* s;
	TCase* tc_core;
	s = suite_create("Vector");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_vector_create);
	suite_add_tcase(s, tc_core);

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
