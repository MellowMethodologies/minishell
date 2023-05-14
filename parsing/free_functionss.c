/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functionss.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 10:51:27 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/12 22:45:49 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	free_args(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i++] = NULL;
	}
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
		free(tmp->value);
		free(tmp);
	}
}
