/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:48:03 by khafni            #+#    #+#             */
/*   Updated: 2021/05/20 17:24:17 by khafni           ###   ########.fr       */
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
** private struct and methods
*/

t_cmd_tables_array  *cmd_tables_array(char *parsing_text)
{
    t_dlist list;
    t_cmd_tables_array *cmds_arr;
    int             i;
    
    i = 0;
    cmds_arr = malloc(sizeof(t_cmd_tables_array));
    list = cmd_tables(parsing_text);
    cmds_arr->n_commands = list->len;
    cmds_arr->commands = malloc(cmds_arr->n_commands + 1);
    dlist_move_cursor_to_head(list);
    while (list->cursor_n != list->sentinel)
    {
        cmds_arr->commands[i] = list->cursor_n->value; 
        dlist_move_cursor_to_next(list);
        i++;
    }
    cmds_arr->commands[i] = NULL; 
    dlist_destroy(list);
}

void cmd_tables_array_destroy(t_cmd_tables_array *cmds_array)
{
    int i;

    i = 0;
    while (i < cmds_array->n_commands)
    {
        command_table_destroy(cmds_array->commands[i]);
        i++;
    }
    free(cmds_array);
}