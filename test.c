#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "dlist/dlists.h"
#include "CPCA/generic_parrays/garrptr.h"
#include "command_table.h"

int main(int argc, char **argv, char **env)
{
    t_arrptr pls = get_pipelines(" l> ls>r>>f1>f2 ok>32 cat f");
    //t_arrptr pls = get_pipelines("ls -a > file.1");
    t_tokens tk;
    for (int i = 0; i < pls->len; i++)
    {
        t_pipeline p = arrptr_get(pls, i);
        t_tokens tks = tokens(p);
        tokens_split_w_red(tks); 
       // printf("-----------\n");
    }
    return (0);
}
