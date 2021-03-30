/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:01:06 by khafni            #+#    #+#             */
/*   Updated: 2021/03/30 16:44:27 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H
# include "CPCA/generic_parrays/garrptr.h"
# include "pipelines.h"
# include "dlist/dlists.h"

typedef	struct	s_commands_table *t_commands_table;

struct	s_commands_table
{	
	char			*command;
	t_arrptr		args;
    int             input;
    int             output;
    t_dlist         redirections;
    char	        is_after_p_or_sc;
};

t_commands_table	cmd_table(t_pipeline pl, char **env);

void				cmd_table_destroy(t_commands_table cmd_tab);

void				get_command(t_commands_table cmd_tab);

#endif