/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:49:12 by khafni            #+#    #+#             */
/*   Updated: 2021/03/30 16:58:33 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

t_commands_table	cmd_table(t_pipeline pl)
{
	t_commands_table	ct;

	ct = malloc(sizeof(struct s_commands_table));
	ct->args = empty_arrptr_create(free);
	ct->redirections = dlist_empty_create(free, NULL, NULL);
	get_command(ct);
	return (ct);
}

void				cmd_table_destroy(t_commands_table cmd_tab)
{
	free(cmd_tab->command);
	arrptr_destroy(cmd_tab->args);
	dlist_destroy(cmd_tab->redirections);
	free(cmd_tab);
}

void				get_command(t_commands_table cmd_tab)
{
	
}