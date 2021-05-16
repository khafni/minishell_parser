#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[], char **envp)
{
    char *term_type = getenv("TERM");
    /* printf("%s", getenv("TERM"));
    tgetent(NULL, getenv("TERM")); */
    int ret = tgetent(NULL, term_type);
    if (ret != 1)
    {
        printf("can't access termcaps data base the data base");
        return (1);
    }
    printf("%d\n", tgetnum("co"));
    printf("%d\n", tgetflag("os"));
    return (0);
}