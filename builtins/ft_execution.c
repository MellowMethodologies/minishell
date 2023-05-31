/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/31 01:23:53 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_execut_cmnd_one(t_parsed *lexe, t_export **export)
{
	extern char	**environ;
	char		**paths;
	char		*valid_path;
	t_export	*tmp;

	tmp = (*export);
	while (tmp && ft_strcmp("PATH", tmp->variable) != 0)
		tmp = tmp->next;
	if (!tmp)
	{
		write(1, " No such file or directory\n", 27);
		exit(127);
	}
	paths = errs(tmp->value);
	valid_path = ft_valid_path(paths, lexe->args[0]);
	if (valid_path == NULL)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
	execve(valid_path, lexe->args, environ);
	write(2, "command not found\n", 18);
	exit(127);
}

void	check_and_exit_f_ok(void)
{
	write(1, "No such file or directory\n", 26);
	exit(127);
}

void	check_and_exit_x_ok(void)
{
	write(1, "Permission denied\n", 19);
	exit(126);
}

void	ft_execut_cmnd_vv(char **args)
{
	if (args[0][0] == '.' && args[0][1] == '/')
	{
		if (access(args[0], F_OK))
			check_and_exit_f_ok();
		if (access(args[0], X_OK))
			check_and_exit_x_ok();
		exit(127);
	}
	else if (args[0][0] == '/')
	{
		if (access(args[0], F_OK))
			check_and_exit_f_ok();
		if (access(args[0], X_OK))
			check_and_exit_x_ok();
		exit(127);
	}
}

void	ft_execut_cmnd(t_parsed *lexe, t_export **export, t_ex_vars **v)
{
	if (ft_strcmp(lexe->args[0], "echo") == 0)
		ft_echo(lexe);
	else if (ft_strcmp(lexe->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(lexe->args[0], "cd") == 0)
		ft_cd(lexe, export);
	else if (ft_strcmp(lexe->args[0], "export") == 0)
		ft_export(lexe, export);
	else if (ft_strcmp(lexe->args[0], "unset") == 0)
		ft_unset(lexe, export);
	else if (ft_strcmp(lexe->args[0], "env") == 0)
		show_env(export, lexe);
	else if (ft_strcmp(lexe->args[0], "exit") == 0)
		ft_exit(lexe, v);
	else
		ft_execut_cmnd_one(lexe, export);
}
