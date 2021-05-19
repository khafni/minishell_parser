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

void enableRawMode()
{
	struct termios raw;
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
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

int main()
{
	tgetent(getenv("TERM"), NULL);
	t_dlist dl = dlist_empty_create(free, NULL, NULL);
	t_rstr rs = rstr_create(0);
	char c = 0;
	int d;
	ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", 1);
	ft_putstr_fd("\x1B[32m", 1);
	ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", 1);
	while (1)
	{
		tputs(tgetstr("ce", NULL), 1, putchar);		
				/* ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", 1);
		ft_putstr_fd("\x1B[32m", 1);
		ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", 1); */
		//scanf("%d", &d);
		while ((c = get_char()))
		{
			if (c == KEY_UP_D)
			{
				if (dl->cursor_n == dl->sentinel)
					continue;
				dlist_move_cursor_to_next(dl);
				if (dl->cursor_n != dl->sentinel)
				{
					/* ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", 1);
					ft_putstr_fd("\x1B[32m", 1);
					ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", 1); */
					tputs(tgetstr("cd", NULL), 1, putchar);
					printf("%s\n", dl->cursor_n->value);
					tputs(tgetstr("cd", NULL), 1, putchar);
				}
			}
			else if (c == KEY_UP_U)
			{
				if (dl->cursor_p == dl->sentinel)
					continue;
				dlist_move_cursor_to_previous(dl);
				if (dl->cursor_n != dl->sentinel)
				{
					/* ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", 1);
					ft_putstr_fd("\x1B[32m", 1);
					ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", 1); */
					tputs(tgetstr("cd", NULL), 1, putchar);
					printf("%s\n", dl->cursor_n->value);
					tputs(tgetstr("cd", NULL), 1, putchar);
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
				ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", 1);
				ft_putstr_fd("\x1B[32m", 1);
				ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", 1);
				rstr_clear(rs);
			}
			c = 0;
		}
	}
	return 0;
}

/* int main()
{
	t_dlist dl = dlist_empty_create(free, 0, 0);
	return (0);
} */