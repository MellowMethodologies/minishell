#include "../mini_shell.h"

void ft_last_del_head(t_export **node)
{
    (*node) = (*node)->next;
}

void ft_last_del_node(t_export **node, t_export **prev_node)
{
    (*prev_node)->next = (*prev_node)->next->next;
}

void ft_delet_node(char *str, t_export **export)
{
    t_export *prev_node = (*export);
    t_export *node = (*export);

    if(strcmp(str, node->variable) == 0)
    {
        ft_last_del_head(&node);
        return;
    }
    else
    {
        if(node->next)
            node = node->next;
    }
    while(node)
    {
        if(strcmp(str, node->variable) == 0)
        {
            ft_last_del_node(&node, &prev_node);
            return;
        }
        else
        {
            node = node->next;
            prev_node = prev_node->next;
        }
    }

}

void    ft_unset(t_parsed *lexe, t_export **export)
{
    if(strcmp(lexe->args[0], "unset") && lexe->args[1] == NULL)
        return ;
    int i = 1;
    while(lexe->args[i])
    {
        ft_delet_node(lexe->args[i], export);
        i++;
    }

}