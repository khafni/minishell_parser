/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:49:12 by khafni            #+#    #+#             */
/*   Updated: 2021/04/03 19:52:07 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

t_commands_table	cmd_table(t_pipeline pl, char **env)
{
	t_commands_table	ct;
	
	ct = malloc(sizeof(struct s_commands_table));
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
	t_tokens tks;

	tks = tokens(pl);
	cmd_table_fill_tokens(cmdt, tks);
	cmd_table_fill_input(cmdt, tks);
	cmd_table_fill_output(cmdt, tks);
	cmd_table_fill_append(cmdt, tks);
	tokens_destroy(tks);	
}

void                cmd_table_fill_tokens(t_commands_table cmdt, t_tokens tks)
{
	int i;
	char *str;
	char *str_m;	

	i = 0;
	while (i < tks->tokens->len)
	{
		str = arrptr_get(tks->tokens, i);
		str_m = arrptr_get(tks->tokens_masks, i);
		if (i == 0 && str[0] == '')
		i++;
	}
}

void                cmd_table_fill_input(t_commands_table cmdt, t_tokens tks);
void                cmd_table_fill_output(t_commands_table cmdt, t_tokens tks);
void                cmd_table_fill_append(t_commands_table cmdt, t_tokens tks);

