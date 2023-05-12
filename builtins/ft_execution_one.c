/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/12 03:45:21 by isbarka          ###   ########.fr       */
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

void	ft_exit_1( t_parsed **tmp, int i, t_export **export)
{
	if ((*tmp)->args[1] == NULL)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else if ((*tmp)->args[1] != NULL && (*tmp)->args[2] != NULL)
	{
		write(1, "exit: too many arguments\n", 25);
		ft_change_exit_st(export, 1);
		return ;
	}
	while ((*tmp)->args[1][i])
	{
		if (!ft_isdigit((*tmp)->args[1][i]))
		{
			write(1, "exit\n", 5);
			write(1, "exit: ", 25);
			ft_putstr(2, (*tmp)->args[1]);
			write(1, ": numeric argument required\n", 28);
			exit(1);
		}
		i++;
	}
	exit(ft_atoi((*tmp)->args[1]));
}

void	ft_exit(t_parsed *lexe1, t_export **export)
{
	int			i;
	t_parsed	*tmp;

	if (!lexe1 || lexe1->args[0] == NULL)
	{
		return ;
	}	
	i = 0;
	tmp = lexe1;
	if (tmp && strcmp(tmp->args[0], "exit") == 0)
	{
		if (!tmp->next)
		{
			ft_exit_1(&tmp, i, export);
		}
	}
}

void	ft_execution_4(t_parsed *lexe, t_ex_vars **ex_vars, t_export **export)
{
	if (lexe && (!lexe->args[0]
			|| ((strcmp(lexe->args[0], "export") == 0 && lexe->args[1] != NULL)
				|| strcmp(lexe->args[0], "unset") == 0)
			|| strcmp(lexe->args[0], "cd") == 0))
		ft_cmnd_one(lexe, (*ex_vars)->count, 1, export);
	else if (lexe)
	{
		(*ex_vars)->id = fork();
		if ((*ex_vars)->id == -1)
			exit(1);
		if ((*ex_vars)->id == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			ft_cmnd(lexe, (*ex_vars)->count, 1, export);
		}
		wait(&((*ex_vars)->status));
	}
	(*ex_vars)->count = (*ex_vars)->count + 1;
	if (lexe)
		lexe = lexe->next;
	// while (lexe && lexe->args[0] == NULL)
	// 	lexe = lexe->next;
	ft_execution_2(lexe, export, ex_vars);
	
	unlink("/tmp/b.txt");
	unlink("/tmp/a.txt");
}

void	ft_instantiate_export(t_export **export)
{
	t_parsed	*tmp = malloc(sizeof(t_parsed));

	tmp->args = malloc(4 * sizeof(char *));
	tmp->args[0] = strdup("PWD=/Users/isbarka/Desktop/mini_shell2");
	tmp->args[1] = strdup("SHLVL=1");
	tmp->args[2] = strdup("_=/usr/bin/env");
	tmp->args[3] = NULL;
	// if ((*export) == NULL)
	// {
	// 	ft_export(tmp, export);
	// }
	// free(tmp->args[0]);
	// free(tmp->args[1]);
	// free(tmp->args[2]);
	// free(tmp->args);
	// free(tmp);
}

void ft_show_args( t_parsed *lexe)
{
	t_parsed *tmp = lexe;
	int i = 0;
	while(lexe->args[i])
	{
		printf("|%s|\n", lexe->args[i]);
		i++;
	}
}

void	ft_execution(t_parsed *lexe_1, t_export **export, char **env)
{
	ft_show_args(lexe_1);
	write(2, "teet\n", 5);
	t_parsed	*lexe;
	t_ex_vars	*ex_vars;
	ft_instantiate_export(export);
	while (lexe_1 && lexe_1->args[0] == NULL)
	{
		lexe_1 = lexe_1->next;
	}
	ft_exit(lexe_1, export);
	ft_instantiate_ex_vars(&ex_vars, env);
	lexe = lexe_1;
	if (lexe)
		lexe->envs = ex_vars->env;
	ft_execution_4(lexe, &ex_vars, export);
	// free(ex_vars);
}
