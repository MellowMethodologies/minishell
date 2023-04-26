#include "minishell.h"

void    ft_unset(t_parsed *lexe, t_export **export)
{
    if(strcmp(lexe->args[0], "unset") && lexe->args[1] == NULL)
        return ;
    int i = 1;
    while(lexe->args[i])
    {
        ft_lst_delete_node_export(export, lexe->args[i]);
        i++;
    }
}