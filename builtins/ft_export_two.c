/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 02:11:02 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/12 21:30:55 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_add_value_ft(char *str, t_export **export)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp && strcmp(tmp->variable, str_befor_equal(str, 1)) != 0)
		tmp = tmp->next;
	tmp->value = str_after_equal(str, 1);
}

void	make_value_null(char *str, t_export **export)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp && strcmp(tmp->variable, str_befor_equal(str, 1)) != 0)
		tmp = tmp->next;
	tmp->value = NULL;
}

void	ft_add_value(char *str, t_export **export, int there_is_equal)
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
			write(2, "error input\n", 12);
		else
		{
			ft_add_variable(lexe->args[i], export);
			there_is_eq = ft_equal(lexe->args[i], export);
			ft_add_value(lexe->args[i], export, there_is_eq);
		}
		i++;
	}
}

int ft_args_export(char **args)
{
	int i = 1;


	if(args[1] == NULL)
		return 1;
	else
		return 0;
}

void	ft_export(t_parsed *lexe, t_export **export)
{
	int			i;
	int			there_is_equal;
	t_export	*tmp;

	i = 1;
	there_is_equal = -2;
	tmp = (*export);
	
	if (ft_args_export(lexe->args))
	{
		show_export(export, lexe);
		ft_change_exit_st(export, 0);
	}
	else
		ft_export_one(lexe, i, export, there_is_equal);
	if(lexe->args[1] == NULL)
		exit(0);
}
