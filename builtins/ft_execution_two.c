/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/31 01:25:38 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	fill_export_with_1(t_export **export)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp)
	{
		tmp->there_is_equal = 1;
		tmp = tmp->next;
	}
}

void	ft_change_exit_st(t_export **export, int exit_statu)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp && ft_strcmp(tmp->variable, "?") != 0)
		tmp = tmp->next;
	free(tmp->value);
	tmp->value = ft_itoa(exit_statu);
}

void	ft_execution_5(t_ex_vars **ex_vars, t_parsed *lexe, t_export **export)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	lexe->envs = (*ex_vars)->env;
	ft_cmnd(lexe, (*ex_vars)->count, 0, export);
}

void	ft_execution_3(t_parsed *l, t_export **export, t_ex_vars **ex_vars)
{
	int	id;

	while (l && l->args[0] == NULL)
		ignor_lexe(&l);
	if (l)
	{
		if (!l->args[0]
			|| ((ft_strcmp(l->args[0], "export") == 0 && l->args[1] != NULL)
				|| ft_strcmp(l->args[0], "unset") == 0)
			|| ft_strcmp(l->args[0], "cd") == 0)
			ft_cmnd_one(l, export);
		else
		{
			id = fork();
			if (id == -1)
				exit(1);
			if (id == 0)
				ft_execution_5(ex_vars, l, export);
			wait(&((*ex_vars)->status));
		}
	}
	(*ex_vars)->exit_status = WEXITSTATUS((*ex_vars)->status);
	if ((*ex_vars)->exit_status >= 1)
		(*ex_vars)->exit_status = 127;
	g_lobal = (*ex_vars)->exit_status;
}

void	ft_execution_2(t_parsed *l, t_export **export, t_ex_vars **ex_vars)
{
	while (l && l->next)
	{
		while (l && l->args[0] == NULL)
			ignor_lexe(&l);
		if (!l->args[0]
			|| ((ft_strcmp(l->args[0], "export") == 0 && l->args[1] != NULL)
				|| ft_strcmp(l->args[0], "unset") == 0)
			|| ft_strcmp(l->args[0], "cd") == 0)
			ft_cmnd_one(l, export);
		else
		{
			(*ex_vars)->id = fork();
			if ((*ex_vars)->id == -1)
				exit(1);
			if ((*ex_vars)->id == 0)
				ft_execution_5(ex_vars, l, export);
			wait(&((*ex_vars)->status));
		}
		l = l->next;
		(*ex_vars)->count = (*ex_vars)->count + 1;
	}
	ft_execution_3(l, export, ex_vars);
}
