/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_generator.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 17:01:17 by khafni            #+#    #+#             */
/*   Updated: 2021/05/01 17:35:27 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TABLE_GENERATOR_H
# define COMMAND_TABLE_GENERATOR_H

# include "dlist/dlists.h"
# include "CPCA/generic_parrays/garrptr.h"
# include "command_table/command_table.h"

/* typedef struct s_cmd_tables t_cmd_tables;

struct s_cmd_tables
{
    t
}
 */
t_dlist     cmd_tables(char *parsing_text);
t_dlist     
#endif