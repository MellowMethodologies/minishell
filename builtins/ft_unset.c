/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:03:32 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/31 01:08:29 by isbarka          ###   ########.fr       */
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
		if (ft_strcmp(str, (*node)->variable) == 0)
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
	if (ft_strcmp(str, node->variable) == 0)
	{
		ft_last_del_head(export);
		ft_change_exit_st(export, 0);
		return ;
	}
	else
	{
		if (node->next)
			node = node->next;
	}
	ft_delet_node_1(&node, &prev_node, str);
	ft_change_exit_st(export, 0);
}

void	ft_unset(t_parsed *lexe, t_export **export)
{
	int	i;

	ft_change_exit_st(export, 0);
	if (ft_strcmp(lexe->args[0], "unset") && lexe->args[1] == NULL)
		return ;
	i = 1;
	while (lexe->args[i])
	{
		if (error_var(lexe->args[i]) == 1)
		{
			write(2, "not a valid identifier\n", 23);
			ft_change_exit_st(export, 1);
		}
		else
			ft_delet_node(lexe->args[i], export);
		i++;
	}
}
