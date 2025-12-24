#include <check.h>
#include <stdlib.h>
#include "check_matrix_operations.h"
#include "check_find_inverse_matrix.h"

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = matrix_operations_suite();
    sr = srunner_create(s);

    srunner_add_suite(sr, find_inverse_matrix_suite());

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}