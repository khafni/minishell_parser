/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_generator.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 17:01:17 by khafni            #+#    #+#             */
/*   Updated: 2021/05/20 17:24:54 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TABLE_GENERATOR_H
# define COMMAND_TABLE_GENERATOR_H

# include "dlist/dlists.h"
# include "CPCA/generic_parrays/garrptr.h"
# include "command_table/command_table.h"


typedef struct	s_cmd_tables_array
{
	t_command	**commands;
	int			n_commands;
}               t_cmd_tables_array;

t_dlist     cmd_tables(char *parsing_text);
void        cmd_tables_destroy(t_dlist cmd_tables_list);
t_cmd_tables_array  *cmd_tables_array(char *parsing_text)
void cmd_tables_array_destroy(t_cmd_tables_array *cmds_array);

#endif