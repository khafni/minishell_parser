/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:48:03 by khafni            #+#    #+#             */
/*   Updated: 2021/05/21 14:31:50 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table_generator.h"

/*
** private struct and methods
*/

t_dlist     cmd_tables(char *parsing_text)
{
    t_dlist     c_tables;
    t_arrptr    pls;
    t_commands_table ct = NULL;
    t_pipeline p;
    int i;

    i = 0;
    c_tables = dlist_empty_create(NULL, NULL, NULL);
    pls = get_pipelines(parsing_text);
    while (i < pls->len)
    {
        p = arrptr_get(pls, i);
        ct = cmd_table(p, NULL);
        cmd_table_fill(ct, p);
        dlist_pushback(c_tables, ct);
        i++;
    }
    arrptr_destroy(pls);
    return (c_tables);
}

void        cmd_tables_destroy(t_dlist cmd_tables_list)
{
    dlist_destroy(cmd_tables_list);
}

/*
** public struct and methods
*/

t_dlist  cmd_tables_list(char *parsing_text)
{
    t_dlist list_;
    t_commands_table c_tables_tmp;
    
    list_ = cmd_tables(parsing_text);
    dlist_move_cursor_to_head(list_);
    while (list_->cursor_n != list_->sentinel)
    {
        c_tables_tmp =  list_->cursor_n->value;
        list_->cursor_n->value = command_table(c_tables_tmp);
        cmd_table_destroy(c_tables_tmp);
        dlist_move_cursor_to_next(list_);
    }
    list_->destroy = command_table_destroy;
    return (list_);
}

void cmd_tables_list_destroy(t_dlist cmds_array)
{
    dlist_destroy(cmds_array);
}