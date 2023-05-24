/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 02:11:02 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/24 00:33:57 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_add_value_ft(char *str, t_export **export)
{
	t_export	*tmp;
	char		*s1;
	char		*s2;

	s1 = str_befor_equal(str, 1);
	s2 = str_after_equal(str, 1);
	tmp = (*export);
	while (tmp && ft_strcmp(tmp->variable, s1) != 0)
		tmp = tmp->next;
	if (tmp->value)
		free(tmp->value);
	tmp->value = s2;
	free(s1);
}

void	make_value_null(char *str, t_export **export)
{
	t_export	*tmp;
	char		*s;

	s = str_befor_equal(str, 1);
	tmp = (*export);
	while (tmp && ft_strcmp(tmp->variable, s) != 0)
		tmp = tmp->next;
	free(s);
	if (tmp->value)
		free(tmp->value);
	tmp->value = NULL;
}

void	ft_add_value(char *str, t_export **export)
{
	if (plus_equal(str))
	{
		ft_join_value(export, str);
	}
	else if (ft_just_equal(str))
	{
		ft_add_value_ft(str, export);
	}
	else
		make_value_null(str, export);
}

void	ft_export_one(t_parsed *lexe, int i, t_export **export, int there_is_eq)
{
	while (lexe->args[i])
	{
		if (error_var(lexe->args[i]) == 1)
		{
			write(2, "not a valid identifier\n", 23);
			g_lobal = 1;
		}
		else
		{
			ft_add_variable(lexe->args[i], export);
			there_is_eq = ft_equal(lexe->args[i], export);
			ft_add_value(lexe->args[i], export);
		}
		i++;
	}
}

void	ft_export(t_parsed *lexe, t_export **export)
{
	int			i;
	int			there_is_equal;

	i = 1;
	there_is_equal = -2;
	if (lexe->args[1] == NULL)
	{
		show_export(export);
		g_lobal = 0;
	}
	else
		ft_export_one(lexe, i, export, there_is_equal);
	if (lexe->args[1] == NULL)
		exit(0);
}
