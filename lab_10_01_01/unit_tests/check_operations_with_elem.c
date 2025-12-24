#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "list_struct.h"
#include "operations_with_elem.h"
#include "operations_with_list.h"
#include "data.h"
#include "errors.h"
#include "memory_alloc.h"

static node_t *create_test_node(const char *surname, int goals)
{
    node_t *new_node = NULL;
    create_footballer_node(surname, goals, &new_node);
    return new_node;
}

START_TEST(test_create_success)
{
    node_t *new_node = NULL;
    error_t rc = create_footballer_node("Zidane", 10, &new_node);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(new_node);
    ck_assert_ptr_nonnull(new_node->data);
    ck_assert_ptr_eq(new_node->next, NULL);

    footballer_t *fb = (footballer_t*)new_node->data;
    ck_assert_str_eq(fb->surname, "Zidane");
    ck_assert_int_eq(fb->goals_count, 10);

    if (new_node)
        delete_elem(&new_node, new_node); 
}
END_TEST

START_TEST(test_create_null_pointer)
{
    error_t rc = create_footballer_node("Zidane", 10, NULL);
    ck_assert_int_ne(rc, OK);
    
    node_t *new_node = NULL;
    rc = create_footballer_node(NULL, 10, &new_node);
    ck_assert_int_ne(rc, OK);
    ck_assert_ptr_eq(new_node, NULL); 
}
END_TEST

START_TEST(test_delete_head)
{
    node_t *head = create_test_node("A", 10);
    node_t *second_node = create_test_node("B", 5);
    add_node_to_list(&head, second_node);

    node_t *to_delete = head;
    delete_elem(&head, to_delete);
    ck_assert_ptr_eq(head, second_node);
    
    list_delete(&head);
}
END_TEST

START_TEST(test_delete_middle)
{
    node_t *head = create_test_node("A", 10);
    node_t *b_node = create_test_node("B", 5);
    node_t *c_node = create_test_node("C", 1);
    add_node_to_list(&head, b_node);
    add_node_to_list(&head, c_node);

    delete_elem(&head, b_node); 
    ck_assert_ptr_eq(head->next, c_node); 
    
    list_delete(&head);
}
END_TEST

Suite *operations_with_elem_suite(void)
{
    Suite *s;
    TCase *tc_elem;

    s = suite_create("OperationsWithElem");
    tc_elem = tcase_create("Core");

    tcase_add_test(tc_elem, test_create_success);
    tcase_add_test(tc_elem, test_create_null_pointer);
    
    tcase_add_test(tc_elem, test_delete_head);
    tcase_add_test(tc_elem, test_delete_middle);
    
    suite_add_tcase(s, tc_elem);
    return s;
}