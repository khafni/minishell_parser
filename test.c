#include <stdio.h>
#include <stdlib.h>
#include "pipelines.h"
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
    t_arrptr pls = get_pipelines(">>f2 ls>file1 -a");
    //t_arrptr pls = get_pipelines("ls -a > file.1");
    t_tokens tk;
    for (int i = 0; i < pls->len; i++)
    {
        t_pipeline p = arrptr_get(pls, i);
        t_commands_table cmd = cmd_table(p, env);
        cmd_table_fill(cmd, p);


        for (int i = 0; i < cmd->tokens->len; i++)
        {
            printf("%s\n", arrptr_get(cmd->tokens, i));
        }
        printf("-----------\n");
    }
    return (0);
}