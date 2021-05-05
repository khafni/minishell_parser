#include <stdio.h>
#include <stdlib.h>
#include "command_table_generator.h"

int main(int argc, char **argv, char **env)
{
    t_commands_table cmd;
    t_dlist c_lists = cmd_tables(">> a_f1 <i_f1 \"tok1 tok2\" <i_f2 tok3 <i_f3 tok4>o_f1>>a_f2>o_f2 tok5 tok6 < i_f4 >> a_f3 | > o_f3 tok7 >o_f4>>a_f4 ; htop");
    dlist_move_cursor_to_head(c_lists);
    while (c_lists->cursor_n != c_lists->sentinel)
    {
        cmd = c_lists->cursor_n->value;
        for (int i = 0; i < cmd->tokens->len; i++)
            printf("%s end\n", (char*)arrptr_get(cmd->tokens, i));
        dlist_move_cursor_to_next(c_lists);
    }
    cmd_tables_destroy(c_lists); 
    return (0);
}
