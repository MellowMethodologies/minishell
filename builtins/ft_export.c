/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 02:11:02 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/31 01:08:29 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	there_already(char *str1, t_export **export)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp)
	{
		if (ft_strcmp(str1, tmp->variable) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_add_variable(char *str, t_export **export)
{
	char		*str1;

	str1 = str_befor_equal(str, 1);
	if (there_already(str1, export))
	{
		free(str1);
		return ;
	}
	else
	{
		ft_lstadd_back_texport(export, ft_lstnew_texport(str1));
	}
}

int	error_var_1(char *str, int count)
{
	if (str[count] && str[count] == '+')
	{
		if (str[count + 1] && str[count + 1] != '=')
			return (1);
	}
	return (0);
}

int	error_var(char *str)
{
	int	count;

	count = 0;
	if ((str[count] >= 'a' && str[count] <= 'z')
		|| (str[count] >= 'A' && str[count] <= 'Z')
		|| str[count] == '_')
	{
	}
	else
		return (1);
	count++;
	while (str[count] && str[count] != '=' && str[count] != '+')
	{
		if ((str[count] >= 'a' && str[count] <= 'z')
			|| (str[count] >= 'A' && str[count] <= 'Z') || str[count] == '_'
			|| (str[count] >= '0' && str[count] <= '9'))
		{
		}
		else
			return (1);
		count++;
	}
	return (error_var_1(str, count));
}

int	there_is_equal(char *str)
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
