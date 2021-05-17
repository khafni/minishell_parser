#include <curses.h>
#include <unistd.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "dlist/dlists.h"

#define KEY_UP_U 4283163
#define KEY_UP_D 4348699

int ft_putchar(int c)
{
    int r = write(1, &c, 1);
    return (r);
}

void enableRawMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &raw);
  raw.c_lflag &= ~(ECHO);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int	read_c(void)
{
	char			c;
	int				total;
	int				ret;
	struct termios	term;
	struct termios	init;

	tcgetattr(0, &term);
	tcgetattr(0, &init);
	term.c_lflag &= ~ (ICANON | ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	ret = read(0, &c, 1);
	while (ret <= 0)
		ret = read(0, &c, 1);
	total += c;
	while (read(0, &c, 1) > 0)
		total += c;
	tcsetattr(0, TCSANOW, &init);
	return (total);
}

int main(int argc, char *argv[], char **envp)
{
    char *term_type = getenv("TERM");
    //printf("%s", getenv("TERM"));
    tgetent(NULL, getenv("TERM"));
    int ret = tgetent(NULL, term_type);
    if (ret != 1)
    {
         printf("can't access termcaps data base the data base");
         return (1);
     }
    
    t_rstr rs;
    t_dlist dl = dlist_empty_create(free, NULL, NULL);
    rs = rstr_create(0);
    struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	int c = 0;

	while (read(0, &c, sizeof(c)) > 0)
	{
        if (dl->len && c == KEY_UP_D)
        {
            
            //break ;
            //tputs(tgetstr("cl", NULL), 1, ft_putchar);
            if (dl->cursor_n != dl->sentinel)
            {
                dlist_move_cursor_to_next(dl);
                //if (dl->cursor_n->value != NULL)
                if (dl->cursor_n->value)
                    printf("%s\n", dl->cursor_n->value);
                //printf("%zu\n", dl->len);
            }
        }
        else if (dl->len && c == KEY_UP_U)
        {
            
            //break ;
            //tputs(tgetstr("cl", NULL), 1, ft_putchar);
            if (dl->cursor_p != dl->sentinel)
                dlist_move_cursor_to_previous(dl);
            //if (dl->len)
            printf("%s\n", dl->cursor_n->value);
        }
        
        else if (c != 10)
        {
            write(1, &c, 1);
           rstr_add(rs, c);
        }
        else if (c == 10 && rs->len)
        {
            dlist_pushback(dl, rstr_to_cstr(rs));
            printf("\n");
            rstr_clear(rs);
        }
		/* printf("keycode: %d\n", c);
        if (c == 'q')
            break ; */
        c = 0;
	}
    /* dlist_move_cursor_to_head(dl);
    while (dl->cursor_n != dl->sentinel)
    {
        printf("%s\n", dl->cursor_n->value);
        dlist_move_cursor_to_next(dl);
    } */
    return (0);
}