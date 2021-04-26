/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:01:06 by khafni            #+#    #+#             */
/*   Updated: 2021/04/26 15:10:09 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H
# include "../CPCA/generic_parrays/garrptr.h"
# include "../pipelines.h"
# include "../dlist/dlists.h"

typedef	struct	s_commands_table *t_commands_table;

struct	s_commands_table
{
    t_tokens        tokens_unproccessed;	
    t_arrptr        tokens;
    t_arrptr        input_files;
    t_arrptr        output_files;
    t_arrptr        append_files;
};

t_commands_table	cmd_table(t_pipeline pl, char **env);
void                cmd_table_fill(t_commands_table cmdt, t_pipeline pl);
/*
**  handle when a command and a redirection symbol are sticked together
** in one word by splitting them & also splits rederection signs and their files
** if they're stuck together
*/

void                cmd_table_fill_tokens(t_commands_table cmdt);
void                cmd_table_fill_input(t_commands_table cmdt);
void                cmd_table_fill_output(t_commands_table cmdt);
void                cmd_table_fill_append(t_commands_table cmdt);

void				cmd_table_destroy(t_commands_table cmd_tab);



#endif