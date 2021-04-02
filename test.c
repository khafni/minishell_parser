#include <stdio.h>
#include <stdlib.h>
#include "pipelines.h"

int main(int argc, char **argv, char **env)
{
    t_arrptr pls = get_pipelines("\"ls\";echo");
    for (int i = 0; i < pls->len; i++)
    {
        t_pipeline p = arrptr_get(pls, i);
        printf("%s\n%s\n", p->cmd_line, p->cmd_line_m);
    }
    return (0);
}