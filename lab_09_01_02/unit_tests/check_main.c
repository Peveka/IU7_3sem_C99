#include <check.h>
#include <stdlib.h>

Suite *struct_sort_suite(void);
Suite *struct_io_suite(void);
Suite *io_suite(void);

int main(void)
{
    int number_failed;
    SRunner *sr;

    sr = srunner_create(struct_sort_suite());
    srunner_add_suite(sr, struct_io_suite());
    srunner_add_suite(sr, io_suite());

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}