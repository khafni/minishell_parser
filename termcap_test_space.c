#include <curses.h>
#include <unistd.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "dlist/dlists.h"
#include "CPCA/generic_parrays/garrptr.h"

#define KEY_UP_U  65
#define KEY_UP_D 66

int ft_putchar(int c)
{
    int r = write(1, &c, 1);
    return (r);
}

struct termios orig_termios;

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  //raw.c_lflag &= ~(ECHO | ICANON);
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

int             get_char()
{
        char    c;
        int     total;
        struct termios term, init;
        tcgetattr(0, &term);
        tcgetattr(0, &init);
        term.c_lflag &= ~(ICANON | ECHO);
        term.c_cc[VMIN] = 0;
        term.c_cc[VTIME] = 0;
        tcsetattr(0, TCSANOW, &term);
        total = 0;
        while (read(0, &c, 1) <= 0);
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
    int i = 0;
    t_arrptr arr = empty_arrptr_create(free);
    rs = rstr_create(0);
    enableRawMode();
	int c = 0;

	while(read(STDIN_FILENO, &c, 1) == 1)
	{
        /* printf("%d\n", c);
        continue; */
        //printf("%d\n", i); 
        if (c == KEY_UP_D)
        {
           /*  if (i < arr->len)
                i++; */
            //printf("%d\n", i);
            printf("%s\n", arrptr_get(arr, i)); 
            //tputs(tgetstr("cl", NULL), 1, ft_putchar);
            /* if (dl->cursor_n != dl->sentinel)
            {
                dlist_move_cursor_to_next(dl);
                //if (dl->cursor_n->value != NULL)
                if (dl->cursor_n->value)
                    printf("%s\n", dl->cursor_n->value);
                //printf("%zu\n", dl->len);
            } */
        }
        else if (c == KEY_UP_U)
        {
            /* if (i > 0)
                i--; */
            //printf("%d\n", i);
            printf("%s\n", arrptr_get(arr, i)); 
            //break ;
            //tputs(tgetstr("cl", NULL), 1, ft_putchar);
            /* if (dl->cursor_p != dl->sentinel)
                dlist_move_cursor_to_previous(dl);
            //if (dl->len)
            printf("%s\n", dl->cursor_n->value); */
        }
        
        else if (c != 10)
        {
            //write(1, &c, 1);
            rstr_add(rs, (char)c);
        }
        else if (c == 10 && rs->len)
        {
            //dlist_pushback(dl, rstr_to_cstr(rs));
            arrptr_add(arr, rstr_to_cstr(rs));
            i = arr->len - 1;
            printf("\n");
            rstr_clear(rs);
        }
		printf("keycode: %d\n", c);
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