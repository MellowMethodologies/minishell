#include "minishell.h"

void ft_lst_delete_node_export(t_export **export, char *str)
{
    t_export *node_to_delete = (*export);
    t_export *previous_node = (*export);
    int check = 0;
    while(node_to_delete && strcmp(node_to_delete->variable, str) != 0)
    {
        if(check != 0)
            previous_node = previous_node->next;
        check = 1;
        node_to_delete = node_to_delete->next;
    }
    if(node_to_delete && node_to_delete->next)
        previous_node->next = node_to_delete->next;
    node_to_delete = NULL;
}

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