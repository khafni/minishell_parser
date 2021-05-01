#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "dlist/dlists.h"
#include "CPCA/generic_parrays/garrptr.h"
#include "command_table/command_table.h"

int main(int argc, char **argv, char **env)
{
    //t_arrptr pls = get_pipelines(">> a_f1 <i_f1 tok1 tok2 <i_f2 tok3 <i_f3 tok4>o_f1>>a_f2>o_f2 tok5 tok6 < i_f4 >> a_f3 | > o_f3 lol >o_f4>>a_f4");
    t_arrptr pls = get_pipelines(">> a_f1 <i_f1 tok1 tok2 <i_f2 tok3 <i_f3 tok4>o_f1>>a_f2>o_f2 tok5 tok6 < i_f4 >> a_f3 | > o_f3 tok7 >o_f4>>a_f4");
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

        /* for (int i = 0; i < ct->input_files->len; i++)
        {
            printf("%s end\n", arrptr_get(ct->input_files, i));
        } */

        /* for (int i = 0; i < ct->output_files->len; i++)
        {
            printf("%s end\n", arrptr_get(ct->output_files, i));
        } */

        /* for (int i = 0; i < ct->tokens->len; i++)
        {
            printf("%s end\n", arrptr_get(ct->tokens, i));
        } */

        for (int i = 0; i < ct->append_files->len; i++)
        {
            printf("%s end\n", arrptr_get(ct->append_files, i));
        }
        cmd_table_destroy(ct);
    }
    return (0);
}
