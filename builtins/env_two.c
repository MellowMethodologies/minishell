/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:13:44 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/09 22:38:43 by isbarka          ###   ########.fr       */
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

void	show_env(t_export **export, t_parsed *lexe)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp)
	{
		if (strcmp(tmp->variable, "?") == 0)
			tmp = tmp->next;
		if (tmp && tmp->there_is_equal == 0)
		{
		}
		else if (tmp && tmp->there_is_equal == 1 && tmp->value == NULL)
		{
			ft_putstr_fd(tmp->variable, 1);
			write(1, "=", 2);
			write(1, "\n", 1);
		}
		else if (tmp)
			ft_print_strs(&tmp);
		if (tmp)
			tmp = tmp->next;
	}
	exit(0);
}