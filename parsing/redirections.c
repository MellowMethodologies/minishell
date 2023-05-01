/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:03:08 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/02 00:46:24 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	great_red(t_parsed **cmd, t_token *tmp)
{
	int	fd;

	if (!cmd || !tmp->next || !check_arguments(tmp->next->type))
	{
		ft_putstr_fd("syntax error near unexpected token '>\n", 2); 
		return (0);
	}
	else if (tmp->next->ambiguous == 1)
	{
		ft_putstr_fd("ambiguous redirect\n", 2); 
		return (0);
	}
	fd = open(tmp->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("error opening file\n", 2); 
		if (*cmd)
			(*cmd)->args = NULL;
		return (1);
	}
	if (*cmd)
		(*cmd)->out = fd;
	tmp = tmp->next;
	return (1);
}

int	append_red(t_parsed **cmd, t_token *tmp)
{
	int	fd;

	if (!cmd || !tmp->next || !check_arguments(tmp->next-> type))
	{
		tmp = tmp->next;
		ft_putstr_fd("syntax error near unexpected token '>\n", 2); 
		return (0);
	}
	else if (tmp->next->ambiguous == 1)
	{
		ft_putstr_fd("ambiguous redirect\n", 2); 
		return (0);
	}
	fd = open(tmp->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("error opening file\n", 2);
		if (*cmd)
			(*cmd)->args = NULL;
		return (1);
	}
	if (*cmd)
		(*cmd)->out = fd;
	tmp = tmp->next;
	return (1);
}

int	less_red(t_parsed **cmd, t_token *tmp)
{
	int	fd;

	if (!cmd || !tmp->next || !check_arguments(tmp->next-> type))
	{
		tmp = tmp->next;
		ft_putstr_fd("syntax error near unexpected token '<'\n", 2); 
		return (0);
	}
	else if (tmp->next->ambiguous == 1)
	{
		ft_putstr_fd("ambiguous redirect\n", 2); 
		return (0);
	}
	fd = open(tmp->next->value, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("error opening file\n", 2);
		if (*cmd)
			(*cmd)->args = NULL;
		return (1);
	}
	if (*cmd)
		(*cmd)->in = fd;
	tmp = tmp->next;
	return (1);
}