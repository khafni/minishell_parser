#include "dlists.h"

int main()
{
    t_dlist lst = dlist_empty_create(free, NULL, NULL);
    dlist_pushback(lst, strdup("fuck"));
    dlist_destroy(lst);
    return (0);
}