/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functionss.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 10:51:27 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/23 19:02:33 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	free_args(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		str[i++] = NULL;
	}
	if (str)
		free(str);
}

void	free_parsed(t_parsed **lst)
{
	t_parsed	*tmp;

	while (*lst)
	{
		free_args((*lst)->args);
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp);
	}
}

void	free_tokens(t_token **lst)
{
	t_token	*tmp;

	while (*lst)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		if (tmp->value)
			free(tmp->value);
		if (tmp)
			free(tmp);
	}
}
