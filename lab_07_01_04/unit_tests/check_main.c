#include <check.h>
#include "errors.h"
#include "check_filter.h"
#include "check_sort.h"

int main(void)
{
    int failed_tests = 0;
    Suite *s_key, *s_mysort;
    SRunner *runner;

    s_key = key_suite();
    s_mysort = mysort_suite();

    runner = srunner_create(s_key);
    srunner_add_suite(runner, s_mysort);

    srunner_run_all(runner, CK_VERBOSE);
    failed_tests = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (failed_tests > 0)
        return ERR_UNIT_FAIL;
    return OK;
}