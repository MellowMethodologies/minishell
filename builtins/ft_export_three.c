/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 02:11:02 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/23 22:29:15 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_equal(char *str, t_export **export)
{
	t_export	*tmp;
	char		*s;

	tmp = (*export);
	s = str_befor_equal(str, 1);
	while (tmp && ft_strcmp(s, tmp->variable) != 0)
		tmp = tmp->next;
	free(s);
	if (there_is_equal(str))
	{
		tmp->there_is_equal = 1;
		return (1);
	}
	else
	{
		tmp->there_is_equal = 0;
		return (0);
	}
}

int	plus_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_just_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
