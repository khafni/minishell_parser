/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:49:12 by khafni            #+#    #+#             */
/*   Updated: 2021/04/04 17:49:02 by khafni           ###   ########.fr       */
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

/*
** check if a string contains > or < or >> only
*/

int		check_if_ra_only(char *str)
{
	size_t len;

	len = ft_strlen(str);
	if (len == 1 && (str[0] == '>' || str[0] == '<'))
		return (1);
	if (len == 2 && str[0] == '>' && str[1] == '>')
		return (1);
	return (0);
}

/*
** check if a string contains > or < or >> + some other character/s
*/

int check_if_ra_plus(char *str)
{
	size_t len;

	len = ft_strlen(str);
	if (len > 1 && (str[0] == '>' || str[0] == '<')
	&& (str[1] != '>'))
		return (1);
	if (len > 2 && str[0] == '>' && str[1] == '>')
		return (1);
	return (0);
}

void                cmd_table_fill_tokens(t_commands_table cmdt)
{
	int i;
	char *str;
	char *str_m;	
	t_tokens tks = cmdt->tokens_unproccessed;

	i = 0;
	while (i < cmdt->tokens_unproccessed->tokens->len)
	{
		str = arrptr_get(tks->tokens, i);
		str_m = arrptr_get(tks->tokens_masks, i);
		if (i == 0 && !check_if_ra_only(str_m) && !check_if_ra_plus(str_m))
			arrptr_add(cmdt->tokens, ft_strdup(str));
		if (i > 0)
		{
			if ((!check_if_ra_only((char *)arrptr_get(tks->tokens_masks, i - 1))
			|| check_if_ra_plus((char *)arrptr_get(tks->tokens_masks, i - 1)))
			&& ((!check_if_ra_only((char *)arrptr_get(tks->tokens_masks, i))
			&& !check_if_ra_plus((char *)arrptr_get(tks->tokens_masks, i)))))
				arrptr_add(cmdt->tokens, ft_strdup(str));
		}
		i++;
	}
}

void                cmd_table_fill_input(t_commands_table cmdt)
{
	int i;
	char *str;
	char *str_m;	
	t_tokens tks = cmdt->tokens_unproccessed;

	i = 0;
	while (i < cmdt->tokens_unproccessed->tokens->len)
	{
		str = arrptr_get(tks->tokens, i);
		str_m = arrptr_get(tks->tokens_masks, i);
		if (i == 0 && str[0] != '>' && str[0] != '<' )
			arrptr_add(cmdt->tokens, ft_strdup(str));
			
		if (i > 0)
		{
			if (str[0] != '>' && str[0] != '<'
			&& ((char *)arrptr_get(tks->tokens_masks, i - 1))[0] != '>'
			&& ((char *)arrptr_get(tks->tokens_masks, i - 1))[0] != '<')
				arrptr_add(cmdt->tokens, ft_strdup(str));	
		}
		i++;
	}
}

void                cmd_table_fill_output(t_commands_table cmdt);
void                cmd_table_fill_append(t_commands_table cmdt);

