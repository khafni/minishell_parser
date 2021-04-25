#include <stdio.h>
#include "dlists.h"
void list_test_f(t_dlist l, char *test_str)
{
    dlist_move_cursor_to_head(l);
    while (l->cursor_n != l->sentinel)
    {
        if (strcmp(test_str, l->cursor_n->value) == 0)
        {
            dlist_remove_after_cursor(l, 1);
            dlist_insert_before_cursor(l, strdup("ok-1"));
            dlist_insert_before_cursor(l, strdup("ok-2"));
            dlist_insert_before_cursor(l, strdup("ok-3"));
        }
        dlist_move_cursor_to_next(l);
    }
}

/* int main()
{
    t_dlist l = dlist_empty_create(free, NULL, NULL);
    dlist_insert_before_cursor(l, strdup("ok1"));
    dlist_insert_before_cursor(l, strdup("ok2"));
    dlist_insert_before_cursor(l, strdup("ok3"));
    dlist_insert_before_cursor(l, strdup("ok4"));

    list_test_f(l, "ok3");

    dlist_move_cursor_to_head(l);
    while (l->cursor_n != l->sentinel)
    {
        printf("%s\n", l->cursor_n->value);
        dlist_move_cursor_to_next(l);
    }
    dlist_destroy(l);
    return (0);
} */