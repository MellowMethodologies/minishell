#include "../mini_shell.h"

void ft_delet_head(t_export **export)
{
    t_export *head = (*export);
    if((*export)->next)
    {
        (*export) = (*export)->next;
    }
    free(head->variable);
    if(head->value)
    {
        free(head->value);
    }
}

void ft_delet_node(t_export **node, t_export **pr_node)
{
    if((*node)->next)
    {
        (*pr_node) = (*node)->next;
    }
    else
       (*pr_node)->next = NULL; 
    free((*node)->variable);
    if((*node)->value)
        free((*node)->value);
    (*node) = NULL;
}

void ft_lst_delete_node_export(t_export **export, char *str)
{
    t_export *node = (*export);
    t_export *pr_node = (*export);
    if(strcmp(node->variable, str) == 0)
    {
        ft_delet_head(export);
        return;
    }
    node = node->next;
    while(node && node->next && strcmp(node->variable, str) != 0)
    {
        pr_node = node;
        node = node->next;
    }
    if(node && strcmp(node->variable, str) == 0)
    {
        ft_delet_node(&node, &pr_node);
    }
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