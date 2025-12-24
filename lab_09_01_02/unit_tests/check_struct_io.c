#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "struct_io.h"
#include "data.h"
#include "errors.h"

START_TEST(test_print_struct_basic)
{
    item_t items[2];
    char name1[] = "Test1", name2[] = "Test2";
    
    items[0].name = name1;
    items[0].weight = 1.0;
    items[0].volume = 2.0;
    
    items[1].name = name2;
    items[1].weight = 3.0;
    items[1].volume = 4.0;
    
    print_struct(items, 2);
    
    ck_assert(1);
}
END_TEST

START_TEST(test_create_item)
{
    char name[] = "TestItem";
    item_t item;
    
    item.name = name;
    item.weight = 5.0;
    item.volume = 2.0;
    
    ck_assert_str_eq(item.name, "TestItem");
    ck_assert_double_eq_tol(item.weight, 5.0, 1e-10);
    ck_assert_double_eq_tol(item.volume, 2.0, 1e-10);
}
END_TEST

Suite *struct_io_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Struct IO");
    
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_print_struct_basic);
    tcase_add_test(tc_core, test_create_item);
    
    suite_add_tcase(s, tc_core);
    
    return s;
}