/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:15:55 by aabounak          #+#    #+#             */
/*   Updated: 2021/03/08 14:14:04 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <math.h>
# include <errno.h>
# include <time.h>
# include <sys/wait.h>
# include <string.h>
# include "../libft/libft.h"
# include "../CPCA/generic_parrays/garrptr.h"
# include "../get_next_line/get_next_line.h"


/*
					The way to parse below:

	echo "hello world these characters can't be escaped in double quotes: this one \\ and this one \$ and this one \", example: $PWD" 'literal' \$PWD | grep \P"W"'D';>>2 echo 123 > 1;>1 echo notempty;<1 cat;echo " $PWD " $PWD ' $PWD ' \$PWD "$"PWD '$'PWD
	NNNNW"SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS\LSSSSSSSSSSSSSS\LSSSSSSSSSSSSSS\LSSSSSSSSSSS$VVV"W'LLLLLLL'W\LNNNW|WNNNNW\L"S"'L';22NWNNNNWNNNW>WN;>NWNNNNWNNNNNNNN;<NWNNN;NNNNW"S$VVVS"W$VVVW'LLLLLL'W\LNNNW"S"NNNW'L'NNN
	N = non-literal
	S = semi-literal
	L = literal
	V = env-variable
	22 = redir-append = >>
	> = redir-trunc, itself
	< = redir-in, itself
	; = itself
	| = itself
	' = itself
	" = itself
	\ = itself

*/

/*
	Split Special Characters
*/


typedef struct  s_state
{
        char    skip;
        char    inside_squote;
        char    inside_dquote;
        char    inside_dquotes_sk;
        char    env_variable;
		char    env_variable_dq;
}                               t_state;

typedef struct	s_command_table
{
    char			*cmds;
	char			**args;
	t_list			*input;
	t_list			*output;
	t_list			*errfile;
}				*t_command_table;

/*
	Main Functions
		---> aksh.c | ...
*/
void		askh_loop(void);
int			aksh_launch(char **args);
char		**aksh_split_line(char *line);

/*
	Function Declarations for builtin shell commands:
*/
int			aksh_cd(char **args);
int			aksh_help(char **args);
int			aksh_exit(char **args);

/*
	External Functions
		---> alt_ft_split.c  | ...
*/
t_arrptr	sh_l_split(char const *s);

#endif