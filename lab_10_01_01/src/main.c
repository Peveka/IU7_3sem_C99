#include "errors.h"
#include <stdlib.h> 
#include <stdio.h>
#include "list_struct.h"
#include "operations_with_list.h"
#include "file_io.h"
#include "list_sort.h"
#include "args_handler.h"
#include "compare_functions.h"

int main(int argc, char **argv)
{
    error_t rc = OK;
    node_t *head = NULL; 
    rc = args_handler(argc, argv);
    if (rc == OK)
        {
            const char *file_in = argv[1];
            const char *file_out = argv[2];
            int minimal_goals_count = atoi(argv[3]);
            
            rc = scan_file_data(file_in, &head);
            if (rc == OK)
            {
                list_filter(&head, minimal_goals_count);
                head = sort(head, sort_footballers);
                remove_duplicated(&head, footballers_eq);
                rc = write_file_data(head, file_out);
            }
        }

    list_delete(&head);

    return rc;
}