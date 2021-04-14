/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:03:20 by khafni            #+#    #+#             */
/*   Updated: 2021/04/03 15:05:563 15:05:59 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipelines.h"

t_pipeline	pipeline(char *cmd_line, char *cmd_line_m, char is_after_p_or_sc)
{
	t_pipeline pl;

	pl = malloc(sizeof(struct s_pipeline));
	pl->cmd_line = cmd_line;
	pl->cmd_line_m = cmd_line_m;
	pl->is_after_p_or_sc = is_after_p_or_sc;

	return (pl);
}


void			pipeline_destroy(void *pl_)
{
	t_pipeline	pl;

	pl = (t_pipeline)pl_;
	free(pl->cmd_line);
	free(pl->cmd_line_m);
	free(pl);
}

t_arrptr		get_pipelines(char *str)
{
	int 		i;
	t_arrptr	arr;
	char		*mask;
	t_rstr		tmp_str;
	t_rstr		tmp_str_m;

	i = 0;
	tmp_str = rstr_create(0);
	tmp_str_m = rstr_create(0);
	arr = empty_arrptr_create(pipeline_destroy);
	mask = get_mask(str);
	while (mask[i])
	{
		if (mask[i] != ';' && mask[i] != '|')
		{
			rstr_add(tmp_str, str[i]);
			rstr_add(tmp_str_m, mask[i]);
		}
		else if (mask[i] == ';' || mask[i] == '|')
		{
			if (mask[i] == ';')
				arrptr_add(arr, pipeline(rstr_to_cstr(tmp_str), rstr_to_cstr(tmp_str_m),
					IS_AFTER_SEMICOLON));
			else if (mask[i] == '|')
				arrptr_add(arr, pipeline(rstr_to_cstr(tmp_str), rstr_to_cstr(tmp_str_m),
					IS_AFTER_PIPE));
			rstr_clear(tmp_str);
			rstr_clear(tmp_str_m);
		}
		i++;
	}
	arrptr_add(arr, pipeline(rstr_to_cstr(tmp_str), rstr_to_cstr(tmp_str_m),
		NO_PIPE_OR_SEMICOLON));
	free(mask);
	rstr_destroy(tmp_str);
	rstr_destroy(tmp_str_m);
	return (arr);
}

/*
** tokens take a pipeline aka a cmd_line
** and its mask and returns them as tokens so
** a further parsing on the tokens can be done
** and we can get a command table from every group
** of tokens
*/

t_tokens		tokens(t_pipeline pl)
{
	t_tokens	tk;
	t_rstr		tmp_str;
	t_rstr		tmp_str_m;
	int i;

	tk = malloc(sizeof(struct s_tokens));
	i = 0;
	tmp_str = rstr_create(0);
	tmp_str_m = rstr_create(0);	
	tk->tokens = dlist_empty_create(free, NULL, NULL);
	tk->tokens_masks = dlist_empty_create(free, NULL, NULL);
	while(pl->cmd_line_m[i])
	{
		if (pl->cmd_line_m[i] != 'W')
		{
			rstr_add(tmp_str, pl->cmd_line[i]);
			rstr_add(tmp_str_m, pl->cmd_line_m[i]);
		}
		else if (pl->cmd_line_m[i] == 'W' && tmp_str_m->len > 0)
		{
			dlist_pushback(tk->tokens, rstr_to_cstr(tmp_str));
			dlist_pushback(tk->tokens_masks, rstr_to_cstr(tmp_str_m));
			rstr_clear(tmp_str);
			rstr_clear(tmp_str_m);
		}
		i++;
	}
	if (tmp_str_m->len)
	{
		dlist_pushback(tk->tokens, rstr_to_cstr(tmp_str));
		dlist_pushback(tk->tokens_masks, rstr_to_cstr(tmp_str_m));	
	}
	rstr_destroy(tmp_str);
	rstr_destroy(tmp_str_m);
	return (tk);
}

/* void	tokens_fix_red(t_tokens tks)
{

} */

int				is_reder(char c)
{
	if (c == '<' || c == '>')	
		return (1);
	return (0);
}

int				is_red_cmd_non_split(char *token_)
{
	char *token;	
	int i;
	int r;
	int al;

	i = 0;
	r = 0;
	al = 0;
	token = (char*)token_;	
	while (token[i])
	{
		if (token[i] == '>' || token[i] == '<')
			r = 1;
		else
			al = 1;	
		i++;
	}
	if (r == 1 && al == 1)
		return (1);
	else
		return (0);
}


void			split_token_w_red_help(char *token, int *i, t_arrptr arr)
{
	t_rstr rs;

	rs = rstr_create(1);
	while (token[*i] && (token[*i] == '>' || token[*i] == '<'))
		rstr_add(rs, token[(*i)++]);
	if (rs->len)
		arrptr_add(arr, rstr_to_cstr(rs));
	rstr_clear(rs);
	while (token[*i] && (token[*i] != '>' && token[*i] != '<'))
		rstr_add(rs, token[(*i)++]);
	if (rs->len)
		arrptr_add(arr, rstr_to_cstr(rs));
	rstr_destroy(rs);
}					

/*
**	devide a string that contains a 
**	cmd and redirections/appnds or redirections/appnds
**	with the files names into tokens
*/

t_arrptr		split_token_w_red(char *token)
{
	t_rstr rs;
	t_arrptr	arr;
	int			i;

	if (!ft_strlen(token) || !is_red_cmd_non_split(token))
		return (NULL);
	i = 0;
	rs = rstr_create(0);
	arr = empty_arrptr_create(free);
	while(token[i])
	{
		if (token[i] != '>' && token[i] != '<')
		{
			rstr_add(rs, token[i]);
		}
		else if (token[i] == '>' || token[i] == '<')
		{
			if (rs->len)
				arrptr_add(arr, rstr_to_cstr(rs));
			split_token_w_red_help(token, &i, arr);
		rstr_clear(rs);
			continue ;
		}
		i++;
	}
	return (arr);
}	

void			tokens_rd_expand(t_dlist lst)
{
	dlist_move_cursor_to_head(lst);
	 while (lst->cursor_n != lst->sentinel) 
    {
		if (is_red_cmd_non_split(lst->cursor_n->value))
		{
			split_token_w_red((char*)lst->cursor_n->value);
			printf("------------\n");
		}
        dlist_move_cursor_to_next(lst->tokens);	
	}
}

void			tokens_split_w_red(t_tokens tks)
{	
	dlist_move_cursor_to_head(tks->tokens);
    while (tks->tokens->cursor_n != tks->tokens->sentinel) 
    {
		if (is_red_cmd_non_split(tks->tokens->cursor_n->value))
		{
			split_token_w_red((char*)tks->tokens->cursor_n->value);
			//printf("%s\n", (char*)tks->tokens->cursor_n->value);
			printf("------------\n");
		}
        dlist_move_cursor_to_next(tks->tokens);	
	}
}

void			tokens_destroy(t_tokens tks)
{
	dlist_destroy(tks->tokens);
	dlist_destroy(tks->tokens_masks);	
	free(tks);
}