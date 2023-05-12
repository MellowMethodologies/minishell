/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 02:11:02 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/09 22:51:40 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	there_is_plus_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_join_value(t_export **export, char *str)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp && strcmp(tmp->variable, str_befor_equal(str, 1)) != 0)
		tmp = tmp->next;
	tmp->value = ft_strjoin(tmp->value, str_after_equal(str, 1));
}

int	arg_exist(char *str, t_export **export)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp && strcmp(tmp->variable, str) != 0)
	{
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	return (1);
}

void	show_export_1(t_export **tmp)
{
	if ((*tmp) && (*tmp)->there_is_equal == 0)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((*tmp)->variable, 1);
		write(1, "\n", 1);
	}
	else if ((*tmp) && (*tmp)->there_is_equal == 1 && (*tmp)->value == NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((*tmp)->variable, 1);
		write(1, "=\"\"", 4);
		write(1, "\n", 1);
	}
	else if ((*tmp))
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((*tmp)->variable, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd((*tmp)->value, 1);
		ft_putstr_fd("\"", 1);
		write(1, "\n", 1);
	}
	if ((*tmp))
		(*tmp) = (*tmp)->next;
}

void	show_export(t_export **export, t_parsed *lexe)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp)
	{
		if (strcmp(tmp->variable, "?") == 0)
			tmp = tmp->next;
		show_export_1(&tmp);
	}
}