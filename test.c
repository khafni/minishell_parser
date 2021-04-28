#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "dlist/dlists.h"
#include "CPCA/generic_parrays/garrptr.h"
#include "command_table/command_table.h"

int main(int argc, char **argv, char **env)
{
    t_arrptr pls = get_pipelines("wc ok>r ls>r>>f1>f2 cat f | ok");
    t_commands_table ct = NULL;
    //t_arrptr pls = get_pipelines("ls -a > file.1");
    t_tokens tk;
    for (int i = 0; i < pls->len; i++)
    {
        t_pipeline p = arrptr_get(pls, i);
        t_tokens tks = tokens(p);
        //tokens_split_w_red(tks->tokens);
        ct = cmd_table(p, env);
        cmd_table_fill(ct, p);
        dlist_move_cursor_to_head(tks->tokens_masks);
        cmd_table_destroy(ct);
        //printf("%s\n", p->cmd_line_m);
    }
    return (0);
}
