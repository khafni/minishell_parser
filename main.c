#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include "command_table_generator.h"
#include <term.h>
#define KEY_UP_ -73
#define KEY_DOWN_ -72
# define KEY_REMOVE 127

int main(int argc, char **argv, char **env)
{
    t_command *cmd;
	int i = 0;
    t_dlist c_lists = cmd_tables_list(">> a_f1 <i_f1 \"tok1 tok2\" <i_f2 tok3 <i_f3 tok4>o_f1>>a_f2>o_f2 tok5 tok6 < i_f4 >> a_f3 | > o_f3 tok7 >o_f4>>a_f4 ; \"htop -o >> -l idontknow\" something");
    //t_dlist c_lists = cmd_tables("\"i_f2>ok\"");
    dlist_move_cursor_to_head(c_lists);
    while (c_lists->cursor_n != c_lists->sentinel)
    {
		i = 0;
        cmd = c_lists->cursor_n->value;
		while (cmd->tokens[i])
		{
            printf("%s end\n", cmd->tokens[i]);
			if (cmd->is_after_p_or_sc == IS_AFTER_SEMICOLON)
				printf("------------------\n end of pipeline :) \n-----------------\n\n");
			i++;
		}
        dlist_move_cursor_to_next(c_lists);
    }
    cmd_tables_destroy(c_lists); 
    return (0);
}



void rstr_remove_char(t_rstr rs)
{
	rs->len--;
}
int ft_putchar(int c)
{
	return (write(1, &c, 1));
}


int get_char()
{
	char c;
	int total;
	struct termios term, init;
	tcgetattr(0, &term);
	tcgetattr(0, &init);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	while (read(0, &c, 1) <= 0)
		;
	total += c;
	while (read(0, &c, 1) > 0)
		total += c;
	tcsetattr(0, TCSANOW, &init);
	return (total);
}


void print_repl_prompt(void)
{
	ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", 1);
	ft_putstr_fd("\x1B[32m", 1);
	ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", 1);
}



/* int main()
{
	tgetent(getenv("TERM"), NULL);
    t_dlist c_lists;
	t_dlist dl = dlist_empty_create(free, NULL, NULL);
	t_rstr rs = rstr_create(0);
	char c = 0;
	int d;	
	print_repl_prompt();
	while (1)
	{
		tputs(tgetstr("ce", NULL), 1, ft_putchar);		
		while ((c = get_char()))
		{
			if (c == KEY_REMOVE)
			{
				if (rs->len)
				{
					rstr_remove_char(rs);
					tputs(tgetstr("le", NULL), 1, ft_putchar);
					tputs(tgetstr("sc", NULL), 1, ft_putchar);
					tputs(tgetstr("dc", NULL), 1, ft_putchar);
				}
			}
			else if (ft_isalnum(c) && c != 10)
			{
				write(1, &c, 1);
				rstr_add(rs, (char)c);
			}
			else if (c == 10 && rs->len > 0)
			{
				dlist_move_cursor_to_tail(dl);
				dlist_insert_after_cursor(dl, rstr_to_cstr(rs));
				printf("\n");
				print_repl_prompt();
				rstr_clear(rs);
                //where the parsing line shall be
                c_lists = cmd_tables(dl->cursor_n->value);
                //where the execution line shall be!!!!!

			}
			c = 0;
		}
	}
	return 0;
} */