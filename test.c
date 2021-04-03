#include <stdio.h>
#include <stdlib.h>
#include "pipelines.h"

int main(int argc, char **argv, char **env)
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
}


/* int main(int argc, char **argv, char **env)
{
    t_arrptr pls = get_pipelines("ls -a > 1.file | >ls k");
    t_tokens tk;
    for (int i = 0; i < pls->len; i++)
    {
        t_pipeline p = arrptr_get(pls, i);
        printf("%s\n%s", p->cmd_line, p->cmd_line_m);
        printf("\n-------------------\n");
    }
    return (0);
} */