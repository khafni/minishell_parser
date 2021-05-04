/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:48:03 by khafni            #+#    #+#             */
/*   Updated: 2021/05/03 17:18:58 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table_generator.h"

t_dlist     cmd_tables(char *parsing_text)
{
    t_dlist     c_tables;
    t_arrptr    pls;
    t_commands_table ct = NULL;
    t_pipeline p;
    int i;

    i = 0;
    c_tables = dlist_empty_create(cmd_table_destroy, NULL, NULL);
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