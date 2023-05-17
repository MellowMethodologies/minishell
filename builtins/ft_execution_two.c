/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/17 01:36:58 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int global;

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
	// printf("||%s||", tmp->value);	
	tmp->value = ft_itoa(exit_statu);
}

void	ft_execution_5(t_ex_vars **ex_vars, t_parsed *lexe, t_export **export)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	lexe->envs = (*ex_vars)->env;
	ft_cmnd(lexe, (*ex_vars)->count, 0, export);
}

void	ft_execution_3(t_parsed *lexe, t_export **export, t_ex_vars **ex_vars)
{
	int	id;
	float a = 13.5f;
	 a = 45;

	id = 0;
	while (lexe && lexe->args[0] == NULL)
			ignor_lexe(&lexe);
	if (lexe)
	{
		if (!lexe->args[0]
			|| ((strcmp(lexe->args[0], "export") == 0 && lexe->args[1] != NULL)
				|| ft_strcmp(lexe->args[0], "unset") == 0)
			|| ft_strcmp(lexe->args[0], "cd") == 0)
			ft_cmnd_one(lexe, (*ex_vars)->count, 0, export);
		else
		{
			id = fork();
			if (id == -1)
				exit(1);
			if (id == 0)
			{
				ft_execution_5(ex_vars, lexe, export);
			}
			wait(&((*ex_vars)->status));
		}
	}
	(*ex_vars)->exit_status = WEXITSTATUS((*ex_vars)->status);
	if((*ex_vars)->exit_status >= 1)
		(*ex_vars)->exit_status = 127;
	global = (*ex_vars)->exit_status;
}

void	ft_execution_2(t_parsed *lexe, t_export **export, t_ex_vars **ex_vars)
{
	while (lexe && lexe->next)
	{
		while (lexe && lexe->args[0] == NULL)
			ignor_lexe(&lexe);
		if (!lexe->args[0]
			|| ((strcmp(lexe->args[0], "export") == 0 && lexe->args[1] != NULL)
				|| ft_strcmp(lexe->args[0], "unset") == 0)
			|| ft_strcmp(lexe->args[0], "cd") == 0)
			ft_cmnd_one(lexe, (*ex_vars)->count, 0, export);
		else
		{
			(*ex_vars)->id = fork();
			if ((*ex_vars)->id == -1)
				exit(1);
			if ((*ex_vars)->id == 0)
				ft_execution_5(ex_vars, lexe, export);
			wait(&((*ex_vars)->status));
		}
		lexe = lexe->next;
		(*ex_vars)->count = (*ex_vars)->count + 1;
	}
	ft_execution_3(lexe, export, ex_vars);
}
