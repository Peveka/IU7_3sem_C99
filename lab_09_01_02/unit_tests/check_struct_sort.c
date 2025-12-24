#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "struct_sort.h"
#include "data.h"

START_TEST(test_compare_double_equal)
{
    int result = compare_double(1.0, 1.0, 1e-10);
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_compare_double_greater)
{
    int result = compare_double(2.0, 1.0, 1e-10);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_compare_double_less)
{
    int result = compare_double(1.0, 2.0, 1e-10);
    ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_sort_struct_basic)
{
    item_t items[3];
    char name1[] = "Item1", name2[] = "Item2", name3[] = "Item3";
    
    items[0].name = name1;
    items[0].weight = 6.0;
    items[0].volume = 2.0;  // ratio = 3.0
    
    items[1].name = name2;
    items[1].weight = 4.0;
    items[1].volume = 2.0;  // ratio = 2.0
    
    items[2].name = name3;
    items[2].weight = 10.0;
    items[2].volume = 2.0;  // ratio = 5.0
    
    sort_struct(items, 3);
    
    ck_assert_str_eq(items[0].name, "Item2");  // ratio = 2.0
    ck_assert_str_eq(items[1].name, "Item1");  // ratio = 3.0
    ck_assert_str_eq(items[2].name, "Item3");  // ratio = 5.0
}
END_TEST

START_TEST(test_sort_struct_same_ratio)
{
    item_t items[2];
    char name1[] = "Item1", name2[] = "Item2";
    
    items[0].name = name1;
    items[0].weight = 4.0;
    items[0].volume = 2.0;  // ratio = 2.0
    
    items[1].name = name2;
    items[1].weight = 6.0;
    items[1].volume = 3.0;  // ratio = 2.0
    
    sort_struct(items, 2);
    
    // При одинаковой плотности порядок должен сохраниться (устойчивая сортировка)
    ck_assert_str_eq(items[0].name, "Item1");
    ck_assert_str_eq(items[1].name, "Item2");
}
END_TEST

START_TEST(test_sort_struct_single)
{
    item_t items[1];
    char name[] = "Single";
    
    items[0].name = name;
    items[0].weight = 5.0;
    items[0].volume = 2.0;
    
    sort_struct(items, 1);
    
    ck_assert_str_eq(items[0].name, "Single");
    ck_assert_double_eq_tol(items[0].weight, 5.0, 1e-10);
    ck_assert_double_eq_tol(items[0].volume, 2.0, 1e-10);
}
END_TEST

Suite *struct_sort_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Struct Sort");
    
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_compare_double_equal);
    tcase_add_test(tc_core, test_compare_double_greater);
    tcase_add_test(tc_core, test_compare_double_less);
    tcase_add_test(tc_core, test_sort_struct_basic);
    tcase_add_test(tc_core, test_sort_struct_same_ratio);
    tcase_add_test(tc_core, test_sort_struct_single);
    
    suite_add_tcase(s, tc_core);
    
    return s;
}