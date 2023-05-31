/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:13:44 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/31 01:08:29 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_print_strs(t_export **tmp)
{
	ft_putstr_fd((*tmp)->variable, 1);
	ft_putstr_fd("=", 1);
	ft_putstr_fd((*tmp)->value, 1);
	write(1, "\n", 1);
}

void	show_env_ww(char *str)
{
	ft_putstr_fd(str, 1);
	write(1, "=", 2);
	write(1, "\n", 1);
}

void	show_env(t_export **export, t_parsed *lexe)
{
	t_export	*tmp;

	if (lexe->args[1])
	{
		write(2, "env: asd: No such file or directory\n", 37);
		exit(127);
	}
	tmp = (*export);
	while (tmp)
	{
		if (ft_strcmp(tmp->variable, "?") == 0)
			tmp = tmp->next;
		if (tmp && tmp->there_is_equal == 0)
		{
		}
		else if (tmp && tmp->there_is_equal == 1 && tmp->value == NULL)
		{
			show_env_ww(tmp->variable);
		}
		else if (tmp)
			ft_print_strs(&tmp);
		if (tmp)
			tmp = tmp->next;
	}
	exit(0);
}
