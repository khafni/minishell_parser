#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "dlist/dlists.h"
#include "CPCA/generic_parrays/garrptr.h"
#include "command_table.h"


/* int main(int argc, char **argv, char **env)
{
    t_arrptr pls = get_pipelines("\"ls\" lol;echo | \"ls -a\" | >ls k | wc    -o    ");
    //t_arrptr pls = get_pipelines("ls -a > file.1");
    t_tokens tk;
    for (int i = 0; i < pls->len; i++)
    {
        t_pipeline p = arrptr_get(pls, i);
        tk = tokens(p);
        for (int i = 0; i < tk->tokens_masks->len; i++)
        {
            printf("||%s#%s||\n", arrptr_get(tk->tokens, i), arrptr_get(tk->tokens_masks, i));
        }
        printf("-----------\n");
    }
    return (0);
} */

int main(int argc, char **argv, char **env)
{
    t_arrptr pls = get_pipelines("ls>r>>f1>f2 ok>32 cat");
    //t_arrptr pls = get_pipelines("ls -a > file.1");
    t_tokens tk;
    for (int i = 0; i < pls->len; i++)
    {
        t_pipeline p = arrptr_get(pls, i);
        t_tokens tks = tokens(p);
        tokens_split_w_red(tks); 
        printf("-----------\n");
    }
    return (0);
}
