/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:59:18 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/03 00:33:15 by sbadr            ###   ########.fr       */
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

t_token *rm_space(t_token *lex)
{
	t_token *curr;
	t_token *new_list;
	t_token **tail;

	new_list = NULL;
	tail = &new_list;
	curr = lex;
	while (curr)
	{
		if (curr->type != -1)
		{
			t_token *new_token = malloc(sizeof(t_token));
			if (!new_token)
				return (NULL);
			new_token->value = ft_strdup(curr->value);
			new_token->index = curr->index;
			new_token->type = curr->type;
			new_token->next = NULL;
			*tail = new_token;
			tail = &new_token->next;
		}
		curr = curr->next;
	}
	return (new_list);
}
