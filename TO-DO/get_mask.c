/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mask.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:05:40 by aabounak          #+#    #+#             */
/*   Updated: 2021/03/09 09:42:14 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		init_states(t_state *state)
{
	state->skip = 0;
	state->inside_squote = 0;
	state->inside_dquote = 0;
	state->env_variable = 0;
	state->env_variable_dq = 0;
}
char		get_mask_char_inside_dq(t_state *state, char *s, int i)
{
	if (s[i] == '\\' && state->skip == 0)
		{
			state->skip = 1;
			return ('\\');
		}
	if (state->env_variable_dq == 1)
	{
		if (ft_isalpha(s[i]) || s[i] == '?')
		{
			if (s[i] == '?')
				state->env_variable_dq = 0;
			return ('V');
		}
		state->env_variable = 0;
	}
	if (s[i] == '$')
		{
			state->env_variable_dq = 1;
			return ('$');
		}
	if (s[i] == '\"')
		{
			state->inside_dquote = 0;
			return ('\"');
		}
	return ('S');
}

char		get_mask_character(t_state *state, char *s, int i)
{
	if (state->inside_squote == 1)
	{
		if (s[i] == '\'')
		{
			state->inside_squote = 0;
			return ('\'');
		}
		return ('L');
	}
	if (state->inside_dquote == 1)
		return (get_mask_char_inside_dq(state, s, i));	
	if (state->env_variable == 1)
	{
		if (ft_isalpha(s[i]) || s[i] == '?')
		{
			if (s[i] == '?')
				state->env_variable = 0;
			return ('V');
		}
		state->env_variable = 0;
	}
	else if (s[i] == '$')
	{
		state->env_variable = 1;
		return ('$');
	}
	if (state->skip == 1)
	{
		state->skip = 0;
		return ('L');
	}	
	else if (s[i] == '\\')
	{
		state->skip = 1;
		return ('\\');
	}	
	else if (s[i] == '\'')
	{
		state->inside_squote = 1;
		return ('\'');
	}	
	else if (s[i] == '\"')
	{
		state->inside_dquote = 1;
		return ('\"');
	}
	else if (s[i] == ';')
		return (';');
	else if (s[i] == '|')
		return ('|');	
	else if (s[i] == '>')
		return ('>');	
	else if (s[i] == '<')
		return ('<');
	else if (s[i] == ' ')
		return ('W');
	return ('N');
}

t_rstr		get_mask(char *s)
{
	int			i;
	t_rstr		bitmasked_arr;
	t_state		state;

	i = 0;
	bitmasked_arr = rstr_create(0);
	init_states(&state);
	while (i < ft_strlen(s) && s[i] != '\0')
	{
		rstr_add(bitmasked_arr, get_mask_character(&state, s, i));
		i++;
	}
	return (bitmasked_arr);
} 

int		main(int argc, char *argv[])
{
	(void)argc;
	printf("%s\n", argv[1]);
	t_rstr bitmasked_arr =  get_mask(argv[1]);

	for (int i = 0; i < bitmasked_arr->len; i++)
		printf("%c", rstr_get(bitmasked_arr, i));
	return (0);
}
