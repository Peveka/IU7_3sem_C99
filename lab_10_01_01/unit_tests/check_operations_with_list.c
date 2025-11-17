#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "list_struct.h"
#include "operations_with_elem.h"
#include "operations_with_list.h"
#include "compare_functions.h"
#include "data.h"
#include "errors.h"

Suite *operations_with_elem_suite(void);

node_t *create_test_node(const char *surname, int goals)
{
    node_t *new_node = NULL;
    create_footballer_node(surname, goals, &new_node);
    return new_node;
}

START_TEST(test_add_to_empty)
{
    node_t *head = NULL;
    node_t *new_node = create_test_node("Messi", 10);
    
    error_t rc = add_node_to_list(&head, new_node);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_eq(head, new_node);
    
    list_delete(&head);
}
END_TEST

START_TEST(test_remove_non_adjacent_dupes)
{
    node_t *head = create_test_node("A", 5);
    node_t *b_node = create_test_node("B", 1); 
    node_t *c_node = create_test_node("C", 10); 
    add_node_to_list(&head, b_node);
    add_node_to_list(&head, create_test_node("A", 5));
    add_node_to_list(&head, c_node);
    
    remove_duplicated(&head, footballers_eq);

    ck_assert_ptr_nonnull(head);
    ck_assert_str_eq(((footballer_t*)head->data)->surname, "A");
    ck_assert_ptr_eq(head->next, b_node);
    ck_assert_ptr_eq(head->next->next, c_node);
    ck_assert_ptr_eq(head->next->next->next, NULL);
    
    list_delete(&head);
}
END_TEST

START_TEST(test_remove_full_dupes_list)
{
    node_t *head = create_test_node("A", 5);
    add_node_to_list(&head, create_test_node("A", 5));
    add_node_to_list(&head, create_test_node("A", 5));
    
    remove_duplicated(&head, footballers_eq);

    ck_assert_ptr_nonnull(head);
    ck_assert_ptr_eq(head->next, NULL);
    
    list_delete(&head);
}
END_TEST

START_TEST(test_sort_by_goals_and_surname)
{
    node_t *head = NULL;
    add_node_to_list(&head, create_test_node("D", 10));
    add_node_to_list(&head, create_test_node("A", 5));
    add_node_to_list(&head, create_test_node("C", 10));
    add_node_to_list(&head, create_test_node("B", 5));

    head = sort(head, sort_footballers);
    
    
    node_t *cur = head;
    ck_assert_str_eq(((footballer_t*)cur->data)->surname, "C");
    cur = cur->next;
    ck_assert_str_eq(((footballer_t*)cur->data)->surname, "D");
    cur = cur->next;
    ck_assert_str_eq(((footballer_t*)cur->data)->surname, "A");
    cur = cur->next;
    ck_assert_str_eq(((footballer_t*)cur->data)->surname, "B");

    list_delete(&head);
}
END_TEST

START_TEST(test_sort_single)
{
    node_t *head = create_test_node("Single", 5);
    node_t *original_head = head;
    
    head = sort(head, sort_footballers);
    
    ck_assert_ptr_eq(head, original_head);
    
    list_delete(&head);
}
END_TEST

Suite *operations_with_list_suite(void)
{
    Suite *s;
    TCase *tc_add, *tc_remove, *tc_sort;

    s = suite_create("OperationsWithList");

    tc_add = tcase_create("AddNode");
    tcase_add_test(tc_add, test_add_to_empty);
    suite_add_tcase(s, tc_add);

    tc_remove = tcase_create("RemoveDuplicates");
    tcase_add_test(tc_remove, test_remove_non_adjacent_dupes);
    tcase_add_test(tc_remove, test_remove_full_dupes_list);
    suite_add_tcase(s, tc_remove);

    tc_sort = tcase_create("Sort");
    tcase_add_test(tc_sort, test_sort_by_goals_and_surname);
    tcase_add_test(tc_sort, test_sort_single);
    suite_add_tcase(s, tc_sort);

    return s;
}

int main(void)
{
    int number_failed = 0;
    SRunner *sr;
    sr = srunner_create(operations_with_elem_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);
    sr = srunner_create(operations_with_list_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}