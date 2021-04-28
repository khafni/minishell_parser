/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:49:12 by khafni            #+#    #+#             */
/*   Updated: 2021/04/26 16:21:11 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

t_commands_table	cmd_table(t_pipeline pl, char **env)
{
	t_commands_table	ct;
	
	ct = malloc(sizeof(struct s_commands_table));
	ct->tokens_unproccessed = tokens(pl);
	ct->tokens = empty_arrptr_create(free);
	ct->input_files = empty_arrptr_create(free);
	ct->output_files = empty_arrptr_create(free);
	ct->append_files = empty_arrptr_create(free);
	return (ct);
}

void				cmd_table_destroy(t_commands_table cmd_tab)
{
	arrptr_destroy(cmd_tab->tokens);	
	arrptr_destroy(cmd_tab->input_files);	
	arrptr_destroy(cmd_tab->output_files);	
	arrptr_destroy(cmd_tab->append_files);		
	free(cmd_tab);
}

void                cmd_table_fill(t_commands_table cmdt , t_pipeline pl)
{	
	
	cmd_table_fill_tokens(cmdt);	
	//cmd_table_fill_input(cmdt, tks);
	//cmd_table_fill_output(cmdt, tks);
	//cmd_table_fill_append(cmdt, tks);
}

void                cmd_table_fill_tokens(t_commands_table cmdt)
{
	t_tokens up;

	up = cmdt->tokens_unproccessed;
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		
		dlist_move_cursor_to_next(up->tokens);
	}
}