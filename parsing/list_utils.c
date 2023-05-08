/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:59:18 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/08 18:04:25 by sbadr            ###   ########.fr       */
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

t_token *find_node(t_token *lex, int index)
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
	t_token	*curr;
	t_token	*prev;

	curr = *lex;
	prev = NULL;
	while (curr)
	{
		if (curr->index == -1)
		{
			if (prev)
				prev->next = curr->next;
			else
				*lex = curr->next;
			free(curr);
			curr = *lex;
		}
		else
			prev = curr;
		curr = curr->next;
	}
}
