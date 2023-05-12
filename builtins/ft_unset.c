/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:03:32 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/09 21:09:03 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_last_del_head(t_export **node)
{
	t_export	*tmp;

	tmp = (*node);
	(*node) = (*node)->next;
	free(tmp->variable);
	free(tmp->value);
	free(tmp);
	tmp = NULL;
}

void	ft_last_del_node(t_export **node, t_export **prev_node)
{
	(*prev_node)->next = (*prev_node)->next->next;
	free((*node)->variable);
	free((*node)->value);
	free(*node);
	(*node) = NULL;
}

void	ft_delet_node_1(t_export **node, t_export **prev_node, char *str)
{
	while (*node)
	{
		if (strcmp(str, (*node)->variable) == 0)
		{
			ft_last_del_node(node, prev_node);
			return ;
		}
		else
		{
			(*node) = (*node)->next;
			(*prev_node) = (*prev_node)->next;
		}
	}
}

void	ft_delet_node(char *str, t_export **export)
{
	t_export	*prev_node;
	t_export	*node;

	prev_node = (*export);
	node = (*export);
	if (strcmp(str, node->variable) == 0)
	{
		ft_last_del_head(&node);
		return ;
	}
	else
	{
		if (node->next)
			node = node->next;
	}
	ft_delet_node_1(&node, &prev_node, str);
}

void	ft_unset(t_parsed *lexe, t_export **export)
{
	int	i;

	if (strcmp(lexe->args[0], "unset") && lexe->args[1] == NULL)
		return ;
	i = 1;
	while (lexe->args[i])
	{
		ft_delet_node(lexe->args[i], export);
		i++;
	}
}
