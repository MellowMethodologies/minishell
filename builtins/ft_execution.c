/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/08 20:41:34 by isbarka          ###   ########.fr       */
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
			dup2(fd[1], 0);
		}
		else
		{
			fd[0] = open("/tmp/a.txt", O_CREAT | O_RDWR, 0644);
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
			dup2(fd[0], 1);
		}
		else
		{
			fd[1] = open("/tmp/b.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(fd[1], 1);
			close(fd[1]);
		}
	}
	else if (lexe->out != -2 && lexe->out != 1)
	{
		dup2(lexe->out, 1);
	}
}

char	**errs(char **env)
{
	char	**paths;

	paths = ft_split(ft_path(env), ':');
	return (paths);
}

void	ft_execut_cmnd_one(t_parsed *lexe)
{
	char	**paths;
	char	*valid_path;

	paths = errs(lexe->envs);
	valid_path = ft_valid_path(paths, lexe->args[0]);
	if (valid_path == NULL)
	{
		write(2, "command not found\n", 18);
		exit(-1);
	}
	execve(valid_path, lexe->args, NULL);
	exit(50);
}

void	ft_execut_cmnd(t_parsed *lexe, t_export **export)
{
	if (strcmp(lexe->args[0], "echo") == 0)
		ft_echo(lexe);
	else if (strcmp(lexe->args[0], "pwd") == 0)
		ft_pwd(lexe, export);
	else if (strcmp(lexe->args[0], "cd") == 0)
		ft_cd(lexe, export);
	else if (strcmp(lexe->args[0], "export") == 0)
		ft_export(lexe, export);
	else if (strcmp(lexe->args[0], "unset") == 0)
		ft_unset(lexe, export);
	else if (strcmp(lexe->args[0], "env") == 0)
		show_env(export, lexe);
	else
		ft_execut_cmnd_one(lexe);
}

void	ft_cmnd(t_parsed *lexe, int count, int is_first, t_export **export)
{
	ft_dup(lexe, is_first, count);
	ft_execut_cmnd(lexe, export);
}

void    ft_cmnd_one(t_parsed *lexe, int count, int is_first, t_export **export)
{
	ft_execut_cmnd(lexe, export);
}

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
	while (tmp && strcmp(tmp->variable, "?") != 0)
		tmp = tmp->next;
	tmp->value = ft_itoa(exit_statu);
}

void ft_execution_2(t_parsed *lexe, t_export **export, t_ex_vars **ex_vars)
{
	int	id;

	id = 0;
	if (lexe)
	{
		if (!lexe->args[0]
			|| ((strcmp(lexe->args[0], "export") == 0 && lexe->args[1] != NULL)
				|| strcmp(lexe->args[0], "unset") == 0) || strcmp(lexe->args[0], "cd") == 0)
			ft_cmnd_one(lexe, (*ex_vars)->count, 0, export);
		else
		{
			id = fork();
			if (id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				lexe->envs = (*ex_vars)->env;
				ft_cmnd(lexe, (*ex_vars)->count, 0, export);
			}
			wait(&((*ex_vars)->status));
		}
	}
	(*ex_vars)->exit_status = WEXITSTATUS((*ex_vars)->status);
	ft_change_exit_st(export, (*ex_vars)->exit_status);
}

void	ft_execution_1(t_parsed *lexe, t_export **export, t_ex_vars **ex_vars)
{
	int	id;

	id = 0;
	while (lexe && lexe->next)
	{
		if (!lexe->args[0]
			|| ((strcmp(lexe->args[0], "export") == 0 && lexe->args[1] != NULL)
				|| strcmp(lexe->args[0], "unset") == 0) || strcmp(lexe->args[0], "cd") == 0)
			ft_cmnd_one(lexe, (*ex_vars)->count, 0, export);
		else
		{
			id = fork();
			if (id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				lexe->envs = (*ex_vars)->env;
				ft_cmnd(lexe, (*ex_vars)->count, 0, export);
			}
			wait(&((*ex_vars)->status));
		}
		lexe = lexe->next;
		(*ex_vars)->count = (*ex_vars)->count + 1;
	}
	ft_execution_2(lexe, export, ex_vars);
	
}

void	ft_instantiate_ex_vars(t_ex_vars **ex_vars, char **env)
{
	(*ex_vars) = malloc(sizeof(t_ex_vars));
	(*ex_vars)->count = 0;
	(*ex_vars)->exit_status = 0;
	(*ex_vars)->status = 0;
	(*ex_vars)->count = 0;
	(*ex_vars)->id = 0;
	(*ex_vars)->env = env;
}

void show_args(t_parsed *lexe)
{
	t_parsed *tmp = lexe;
	while(tmp)
	{
		printf("%s\n", tmp->args[0]);
		printf("in = %d\n", tmp->in);
		printf("out = %d\n", tmp->out);
		tmp = tmp->next;
	}
}

void ft_exit(t_parsed *lexe1, t_export **export)
{
	int i = 0;
	t_parsed *tmp = lexe1;
	if (strcmp(tmp->args[0], "exit") == 0)
	{
		if (!tmp->next)
		{
			if(tmp->args[1] == NULL)
			{
				write(1, "exit\n", 5);
				exit(0);
			}
			else if(tmp->args[1] != NULL && tmp->args[2] != NULL)
			{
				write(1, "exit: too many arguments\n", 25);
				ft_change_exit_st(export, 1);
				return ;
			}
			while(tmp->args[1][i])
			{
				if(!ft_isdigit(tmp->args[1][i]))
				{
					write(1, "exit\n", 5);
					write(1, "exit: ", 25);
					ft_putstr(2, tmp->args[1]);
					write(1, ": numeric argument required\n", 28);
					exit(1);
				}
				i++;
			}
			exit(ft_atoi(tmp->args[1])) ;
		}
	}
}

void free_lexe(t_parsed *lexe)
{
	
}

void	ft_execution(t_parsed *lexe_1, t_export **export, char **env)
{
	// s h o w _ a r g s ( l e x e _ 1 ) ; 
	t_parsed	*lexe;
	t_ex_vars	*ex_vars;

	if (lexe_1->args[0] == NULL)
	{
		ft_change_exit_st(export, 1);
		return ;
	}
	ft_exit(lexe_1, export);
	ft_instantiate_ex_vars(&ex_vars, env);
	lexe = lexe_1;
	ex_vars->exit_status = 0;
	ex_vars->count = 0;
	ex_vars->id = 0;
	ex_vars->status = 100;
	lexe->envs = ex_vars->env;
	if (!lexe->args[0]
		|| ((strcmp(lexe->args[0], "export") == 0 && lexe->args[1] != NULL)
			|| strcmp(lexe->args[0], "unset") == 0) || strcmp(lexe->args[0], "cd") == 0)
		ft_cmnd_one(lexe, ex_vars->count, 1, export);
	else
	{
		ex_vars->id  = fork();
		if (ex_vars->id  == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			ft_cmnd(lexe, ex_vars->count, 1, export);
		}
		wait(&(ex_vars->status));
	}
	ex_vars->count = ex_vars->count + 1;
	lexe = lexe->next;
	ft_execution_1(lexe, export, &ex_vars);
	unlink("/tmp/b.txt");
	unlink("/tmp/a.txt");
}
