/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/22 23:11:28 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_dup_1(int is_first, int *fd, int count, t_parsed *lexe)
{
	if (is_first == 0 && lexe->in == -2)
	{
		if (count % 2 == 0)
		{
			fd[1] = open("/tmp/b.txt", O_CREAT | O_RDWR, 0644);
			if (fd[1] == -1)
				exit(1);
			dup2(fd[1], 0);
		}
		else
		{
			fd[0] = open("/tmp/a.txt", O_CREAT | O_RDWR, 0644);
			if (fd[0] == -1)
				exit(1);
			dup2(fd[0], 0);
			close(fd[0]);
		}
	}
	else if (lexe->in != -2 && lexe->in != 0)
		dup2(lexe->in, 0);
}

void	ft_dup(t_parsed *lexe, int is_first, int count)
{
	int	fd[2];

	ft_dup_1(is_first, fd, count, lexe);
	if (lexe->next && lexe->out == -2)
	{
		if (count % 2 == 0)
		{
			fd[0] = open("/tmp/a.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd[0] == -1)
				exit(1);
			dup2(fd[0], 1);
		}
		else
		{
			fd[1] = open("/tmp/b.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd[1] == -1)
				exit(1);
			dup2(fd[1], 1);
			close(fd[1]);
		}
	}
	else if (lexe->out != -2 && lexe->out != 1)
	{
		dup2(lexe->out, 1);
	}
}

char	**errs(char *env)
{
	char	**paths;

	paths = ft_split(env, ':');
	return (paths);
}

void	ft_execut_cmnd_one(t_parsed *lexe, t_export **export)
{
	char	**paths;
	char	*valid_path;
	t_export	*tmp = (*export);
	
	while(tmp && ft_strcmp("PATH", tmp->variable) != 0)
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
	execve(valid_path, lexe->args, NULL);
	write(2, "command not found\n", 18);
	exit(127);
}

void	ft_execut_cmnd(t_parsed *lexe, t_export **export)
{
	if (lexe->args[0][0] == '.' && lexe->args[0][1] == '/')
	{
		if (access(lexe->args[0],F_OK))
		{
			write(1, "No such file or directory\n", 26);
			exit(127);
		}
		if (access(lexe->args[0], X_OK))
		{
			write(1, "Permission denied\n", 19);
			exit(126);
		}
		exit(127);	
	}
	else if (lexe->args[0][0] == '/')
	{
		if (access(lexe->args[0],F_OK))
		{
			write(1, "No such file or directory\n", 26);
			exit(127);
		}
		if (access(lexe->args[0], X_OK ))
		{
			write(1, "Permission denied\n", 19);
			exit(126);
		}
		exit(127);	
	}
	else if (strcmp(lexe->args[0], "echo") == 0)
		ft_echo(lexe);
	else if (strcmp(lexe->args[0], "pwd") == 0)
		ft_pwd();
	else if (strcmp(lexe->args[0], "cd") == 0)
		ft_cd(lexe, export);
	else if (strcmp(lexe->args[0], "export") == 0)
		ft_export(lexe, export);
	else if (strcmp(lexe->args[0], "unset") == 0)
		ft_unset(lexe, export);
	else if (strcmp(lexe->args[0], "env") == 0)
		show_env(export, lexe);
	else if (strcmp(lexe->args[0], "exit") == 0)
		ft_exit(lexe);
	else
		ft_execut_cmnd_one(lexe, export);
}
