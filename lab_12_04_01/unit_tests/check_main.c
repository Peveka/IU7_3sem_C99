#include <check.h>
#include "check_filter.h"
#include "check_sort.h"
#include "errors.h"

int main(void)
{
    int failed = 0;
    Suite *s_filter = key_suite();
    Suite *s_sort = mysort_suite();
    SRunner *runner = srunner_create(s_filter);

    srunner_add_suite(runner, s_sort);

    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? OK : ERR_UNIT_FAIL;
}