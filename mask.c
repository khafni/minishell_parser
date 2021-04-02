/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:05:40 by aabounak          #+#    #+#             */
/*   Updated: 2021/04/02 17:59:15 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mask.h"

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

char	*get_mask(char *s)
{
	int			i;
	int			len;
	char		*dst;
	t_state		state;

	i = 0;
	len = ft_strlen(s);
	init_states(&state);
	dst = (char *)malloc(sizeof(char) + len + 1);
	while (i < len && s[i] != '\0')
	{
		dst[i] = get_mask_character(&state, s, i);
		i++;
	}
	dst[i] = 0;
	return (dst);
}

/* t_arrptr	split_using_mask(char *str, char *str_mask, char del)
{
	
} */
