#include "../mini_shell.h"

void ft_pwd(t_parsed *lexe, t_export **export)
{
    t_export *tmp = (*export);

    while(tmp && strcmp("PWD", tmp->variable) != 0)
        tmp = tmp->next;
    ft_putstr_fd(tmp->value, 1);
    ft_putstr_fd("\n", 1);
    exit(0);
}
