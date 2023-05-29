/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:05:58 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/29 16:23:05 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_token	*ft_lstne(void *value, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->here_me = 0;
	new->ambiguous = 0;
	new->next = NULL;
	return (new);
}

t_export	*ft_lstnew_export(void *var, char *value)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	new->value = value;
	new->variable = var;
	new->there_is_equal = 1;
	new->next = NULL;
	return (new);
}

void	add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	add_back_parsed(t_parsed **lst, t_parsed *new)
{
	t_parsed	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last)
	{
		if (!last -> next)
			break ;
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
}
