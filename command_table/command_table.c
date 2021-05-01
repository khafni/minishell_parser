/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:49:12 by khafni            #+#    #+#             */
/*   Updated: 2021/05/01 13:41:34by khafni           ###   ########.fr       */
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
	cmd_table_fill_input(cmdt);
	cmd_table_fill_output(cmdt);
	cmd_table_fill_append(cmdt);
}

int					is_token_a_r_app_file(t_commands_table cmdt)
{
	t_tokens up;		

	up = cmdt->tokens_unproccessed;	
	if (up->tokens->cursor_p == up->tokens->sentinel)
		return (0);
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (ft_strnstr((char*)(up->tokens->cursor_p->value), ">>", 2))
			return (1);	
		return (0);
	}		
	if (ft_strnstr((char*)(up->tokens->cursor_p->value), ">>", 2))
		return (1);
	return (0);
		
}

void                cmd_table_fill_append(t_commands_table cmdt)
{
	t_tokens up;

	up = cmdt->tokens_unproccessed;
	dlist_move_cursor_to_head(up->tokens);
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		if (is_token_a_r_app_file(cmdt))
			arrptr_add(cmdt->append_files, ft_strdup(up->tokens->cursor_n->value));
		dlist_move_cursor_to_next(up->tokens);
	}
}

int					is_token_a_r_o_file(t_commands_table cmdt)
{
	t_tokens up;		

	up = cmdt->tokens_unproccessed;	
	if (up->tokens->cursor_p == up->tokens->sentinel)
		return (0);
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (*(char*)(up->tokens->cursor_p->value) == '>')
			return (1);	
		return (0);
	}	
	if (*(char*)(up->tokens->cursor_p->value) == '>'
	&& !ft_strnstr((char*)(up->tokens->cursor_p->value), ">>", 2))
		return (1);
	return (0);
		
}

void                cmd_table_fill_output(t_commands_table cmdt)
{
	t_tokens up;

	up = cmdt->tokens_unproccessed;
	dlist_move_cursor_to_head(up->tokens);
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		if (is_token_a_r_o_file(cmdt))
			arrptr_add(cmdt->output_files, ft_strdup(up->tokens->cursor_n->value));
		dlist_move_cursor_to_next(up->tokens);
	}
}

int					is_token_a_r_i_file(t_commands_table cmdt)
{
	t_tokens up;		

	up = cmdt->tokens_unproccessed;	
	if (up->tokens->cursor_p == up->tokens->sentinel)
		return (0);
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (*(char*)(up->tokens->cursor_p->value) == '<')
			return (1);	
		return (0);
	}	
	if (*(char*)(up->tokens->cursor_p->value) == '<')
		return (1);
	return (0);
		
}

void                cmd_table_fill_input(t_commands_table cmdt)
{
	t_tokens up;

	up = cmdt->tokens_unproccessed;
	dlist_move_cursor_to_head(up->tokens);
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		if (is_token_a_r_i_file(cmdt))
			arrptr_add(cmdt->input_files, ft_strdup(up->tokens->cursor_n->value));
		dlist_move_cursor_to_next(up->tokens);
	}
}

int					is_normal_token(t_commands_table cmdt)
{
	t_tokens up;		

	up = cmdt->tokens_unproccessed;	
	if (up->tokens->cursor_p == up->tokens->sentinel)
	{
		if (*(char*)(up->tokens->cursor_n->value) == '>'
		|| *(char*)(up->tokens->cursor_n->value) == '<')
			return (0);	
		return (1);
	}	
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (*(char*)(up->tokens->cursor_p->value) == '>'
		|| *(char*)(up->tokens->cursor_p->value) == '<')
			return (0);	
		return (1);
	}	
		if ((*(char*)(up->tokens->cursor_p->value) == '>'
		|| *(char*)(up->tokens->cursor_p->value) == '<')
		|| (*(char*)(up->tokens->cursor_n->value) == '<')
		|| (*(char*)(up->tokens->cursor_n->value) == '>'))	
			return (0);
		return (1);	
}

void                cmd_table_fill_tokens(t_commands_table cmdt)
{
	t_tokens up;

	up = cmdt->tokens_unproccessed;
	dlist_move_cursor_to_head(up->tokens);
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		if (is_normal_token(cmdt))
			arrptr_add(cmdt->tokens, ft_strdup(up->tokens->cursor_n->value));
		dlist_move_cursor_to_next(up->tokens);
	}
}