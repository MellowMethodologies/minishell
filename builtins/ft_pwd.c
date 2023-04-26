#include "minishell.h"

void ft_pwd(t_parsed *lexe)
{
    char buff[1024];

    getcwd(buff, 1024);
    ft_putstr_fd(buff, 1);
    ft_putstr_fd("\n", 1);
}
