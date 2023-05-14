/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:59:18 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/11 17:10:46 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	indexer(t_token **lex)
{
	t_token	*temp;
	int		i;
	int		count;

	count = 1;
	i = 0;
	temp = *lex;
	while (temp)
	{
		if (temp->type == -1)
			temp->index = -1;
		else
			temp->index = i++;
		temp = temp->next;
	}
}

t_token	*find_node(t_token *lex, int index)
{
	t_token	*temp;

	temp = lex;
	if (index < 0)
		return (NULL);
	while (temp)
	{
		if (temp->index == index)
			return (temp);
		temp = temp ->next;
	}
	return (NULL);
}

void	rm_space(t_token **lex)
{
	t_token	*current;
	t_token	*prev;
	t_token	*temp;

	current = *lex;
	prev = NULL;
	while (current)
	{
		if (current->index == -1)
		{
			if (!prev)
				*lex = current->next;
			else
				prev->next = current->next;
			temp = current;
			current = current->next;
			free(temp);
		}
		else
		{
		prev = current;
		current = current->next;
		}
	}
}
