#include <curses.h>
#include <unistd.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "dlist/dlists.h"
#include "CPCA/generic_parrays/garrptr.h"

#define KEY_UP_U -73
#define KEY_UP_D -72
# define KEY_REMOVE 127

struct s_history_node
{
	char *str_1;
	char *str_2;
};

typedef struct s_history_node *t_history_node;

t_history_node empty_history_node(void)
{
	t_history_node hn;

	hn = malloc(sizeof(struct s_history_node));
	hn->str_1 = NULL;
	hn->str_2 = NULL;
	return (hn);
}

void history_node_destroy(t_history_node hn)
{
	if (hn->str_1)
		free(hn->str_1);
	if (hn->str_2)
		free(hn->str_2);
	free(hn);
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

int main()
{
	tgetent(getenv("TERM"), NULL);
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
			if (c == KEY_UP_D)
			{
				if (dl->cursor_n == dl->sentinel)
					continue;
				dlist_move_cursor_to_next(dl);
				if (dl->cursor_n != dl->sentinel)
				{
					tputs(tgetstr("cr", NULL), 1, ft_putchar);
					tputs(tgetstr("cd", NULL), 1, ft_putchar);
					print_repl_prompt();
					ft_putstr_fd(dl->cursor_n->value, 1);
					tputs(tgetstr("cd", NULL), 1, ft_putchar);
				}
			}
			else if (c == KEY_UP_U)
			{
				if (dl->cursor_p == dl->sentinel)
					continue;
				dlist_move_cursor_to_previous(dl);
				if (dl->cursor_n != dl->sentinel)
				{
					tputs(tgetstr("cr", NULL), 1, ft_putchar);
					tputs(tgetstr("cd", NULL), 1, ft_putchar);
					print_repl_prompt();
					ft_putstr_fd(dl->cursor_n->value, 1);
					cstr_to_rstr_without_n_rs(dl->cursor_n->value, rs);
					tputs(tgetstr("cd", NULL), 1, ft_putchar);
				}
			}
			else if (c == KEY_REMOVE)
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
				//dlist_insert_after_cursor(dl, empty_history_node())
				dlist_insert_after_cursor(dl, rstr_to_cstr(rs));
				printf("\n");
				print_repl_prompt();
				rstr_clear(rs);
			}
			c = 0;
		}
	}
	return 0;
}