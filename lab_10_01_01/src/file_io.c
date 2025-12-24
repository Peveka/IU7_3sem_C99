#include "list_struct.h"
#include "data.h"
#include "errors.h"
#include "operations_with_elem.h"
#include "operations_with_list.h" 
#include <stdio.h>

error_t scan_file_data(const char *filename, node_t **head)
{
    error_t rc = OK;
    FILE *file = NULL;
    char surname[100];
    int goals;
    
    if (filename == NULL || head == NULL)
        rc = ERR_INVALID_DATA;
    
    if (rc == OK)
    {
        file = fopen(filename, "r");
        if (file == NULL)
            rc = ERR_FILE_OPEN;
    }
    
    if (rc == OK)
    {
        while (rc == OK && fscanf(file, "%99s %d", surname, &goals) == 2)
        {
            node_t *new_node = NULL;
            rc = create_footballer_node(surname, goals, &new_node);
            if (rc == OK)
                rc = add_node_to_list(head, new_node);
        }
        
        fclose(file);
    }
    
    return rc;
}

error_t write_file_data(node_t *head, const char *filename)
{
    error_t rc = OK;
    FILE *file = NULL;
    if (filename == NULL)
        rc = ERR_INVALID_DATA;
    
    if (rc == OK)
    {
        file = fopen(filename, "w");
        if (file == NULL)
            rc = ERR_FILE_OPEN;
    }
    
    if (rc == OK)
    {
        node_t *current = head;
        while (current != NULL && rc == OK)
        {
            footballer_t *fb = (footballer_t*)current->data;
            if (fprintf(file, "%s %d\n", fb->surname, fb->goals_count) < 0)
                rc = ERR_NOT_ENOUGH_DATA;
            current = current->next;
        }
        
        fclose(file);
    }
    
    return rc;
}