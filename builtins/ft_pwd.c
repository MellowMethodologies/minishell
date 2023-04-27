#include "minishell.h"

void ft_pwd(t_parsed *lexe)
{
    char *buff;

    getcwd(buff, 1024);
    if(buff == NULL)
    {
        exit(1);
    }
    ft_putstr_fd(buff, 1);
    ft_putstr_fd("\n", 1);
    exit(0);
}
