/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_one_v1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/06/03 15:14:35 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_instantiate_ex_vars(t_ex_vars **ex_vars, char **env)
{
	(*ex_vars) = malloc(sizeof(t_ex_vars));
	if (!(*ex_vars))
		exit(1);
	(*ex_vars)->count = 0;
	(*ex_vars)->exit_status = 0;
	(*ex_vars)->status = 0;
	(*ex_vars)->count = 0;
	(*ex_vars)->id = 0;
	(*ex_vars)->env = env;
}

void	ft_exit_1( t_parsed **tmp, int i)
{
	if ((*tmp)->args[1] == NULL)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else if ((*tmp)->args[1] != NULL && (*tmp)->args[2] != NULL)
	{
		write(1, "exit: too many arguments\n", 25);
		g_lobal = 1;
		return ;
	}
	while ((*tmp)->args[1][i])
	{
		if (!ft_isdigit((*tmp)->args[1][i]))
		{
			write(1, "exit\n", 5);
			write(1, "exit: ", 6);
			ft_putstr(2, (*tmp)->args[1]);
			write(1, ": numeric argument required\n", 28);
			exit(1);
		}
		i++;
	}
	exit(ft_atoi((*tmp)->args[1]));
}

void	ft_exit(t_parsed *lexe1, t_ex_vars **v)
{
	int			i;
	t_parsed	*tmp;

	if (!lexe1 || lexe1->args[0] == NULL)
	{
		return ;
	}	
	i = 0;
	tmp = lexe1;
	if (tmp && ft_strcmp(tmp->args[0], "exit") == 0
		&& (*v)->first_lexe->next == NULL)
	{
		if (!tmp->next)
		{
			ft_exit_1(&tmp, i);
		}
	}
}

void	ft_instantiate_export(t_export **export)
{
	t_parsed	*tmp;

	if (!(*export)->next)
	{
		tmp = malloc(sizeof(t_parsed));
		tmp->args = malloc(5 * sizeof(char *));
		tmp->args[0] = ft_strdup("export");
		tmp->args[1] = ft_strdup("PWD=/Users/isbarka/Desktop/mini_shell2");
		tmp->args[2] = ft_strdup("SHLVL=1");
		tmp->args[3] = ft_strdup("_=/usr/bin/env");
		tmp->args[4] = NULL;
		ft_export(tmp, export);
		free(tmp->args[0]);
		free(tmp->args[1]);
		free(tmp->args[2]);
		free(tmp->args);
		free(tmp);
	}
}

void	ft_show_args( t_parsed *lexe)
{
	int	i;

	i = 0;
	while (lexe->args && lexe->args[i])
	{
		printf("|%s|\n", lexe->args[i]);
		printf("|%d|\n", lexe->args_null);
		i++;
	}
}
