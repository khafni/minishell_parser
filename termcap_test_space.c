#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[], char **envp)
{
    printf("%s", getenv("TERM"));
    tgetent(NULL, getenv("TERM"));
    return (0);
}