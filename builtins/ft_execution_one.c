/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/18 22:49:12 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int global;

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
		global = 1;
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
	if (tmp && ft_strcmp(tmp->args[0], "exit") == 0)
	{
		if (!tmp->next)
		{
			ft_exit_1(&tmp, i, export);
		}
	}
}

void	ft_execution_4(t_parsed *lexe, t_ex_vars **ex_vars, t_export **export)
{
	
}

void	ft_instantiate_export(t_export **export)
{
	if(!(*export)->next)
	{
		t_parsed	*tmp = malloc(sizeof(t_parsed));

		tmp->args = malloc(5 * sizeof(char *));
		tmp->args[0] = strdup("export");
		tmp->args[1] = strdup("PWD=/Users/isbarka/Desktop/mini_shell2");
		tmp->args[2] = strdup("SHLVL=1");
		tmp->args[3] = strdup("_=/usr/bin/env");
		tmp->args[4] = NULL;
		ft_export(tmp, export);
		free(tmp->args[0]);
		free(tmp->args[1]);
		free(tmp->args[2]);
		free(tmp->args);
		free(tmp);
	}
}

void ft_show_args( t_parsed *lexe)
{
	t_parsed *tmp = lexe;
	int i = 0;
	
	while(lexe->args && lexe->args[i])
	{
		printf("|%s|\n", lexe->args[i]);
		i++;
	}
}

void ignor_lexe(t_parsed **lexe)
{
		(*lexe) = (*lexe)->next;
		unlink("/tmp/b.txt");
		unlink("/tmp/a.txt");
}

void ft_show_export( t_export **export)
{
	t_export *tmp = (*export);

	while(tmp)
	{
		printf("!%s!\n",tmp->variable);
		tmp = tmp->next;
	}
}

void exit_( t_export **export, pid_t id, t_parsed *lexe1)
{
	t_parsed *tmp = lexe1;
	t_parsed *lexe = lexe1;
	
	while(tmp)
		tmp = tmp->next;
	pid_t wait1;
	int exit;
	while(lexe)
	{
		if(id == waitpid(-1, &exit, 0))
		{
			if (WIFEXITED(exit))
			{
				if(lexe->args[0] &&(ft_strcmp(lexe->args[0], "cd") == 0 || ft_strcmp(lexe->args[0], "unset") == 0 ||ft_strcmp(lexe->args[0], "exit") == 0 || (ft_strcmp(lexe->args[0], "export") == 0 && lexe->args[1] != NULL)))
				{
				}
				else
					global =  WEXITSTATUS(exit);
			}
		}
		write(2, "test\n", 5);
		lexe = lexe->next;
	}
}

int check_builtins(char **strs)
{
	if(ft_strcmp(strs[0], "cd") == 0 || ft_strcmp(strs[0], "unset") == 0 || ft_strcmp(strs[0], "exit") == 0 || (ft_strcmp(strs[0], "export") == 0 && strs[1] != NULL))
		return 0;
	return 1;
}

void hundle_1(int sig)
{
		global = 130;
}
void hundle_2(int sig)
{
	global = 0;
}

void	ft_execution(t_parsed *lexe1, t_export **export, char **env)
{
	signal(SIGINT, hundle_1);
	signal(SIGQUIT, hundle_2);
	int fd[2];
	int stdin= -1;
	int stdout;
	int save_prev_stdin = -1;
	int ss;
	pid_t id;
	t_parsed *lexe = lexe1;
	while(lexe)
	{

		while(lexe && lexe->args[0] == NULL)
		{
			ss = open("ss", O_CREAT | O_RDWR, 0777);
			stdin = ss;
			lexe = lexe->next;
		}
		stdout = -1;
		if(lexe && lexe->next)
		{
			if (pipe(fd) != -1)
			{
				stdout = fd[1];
			save_prev_stdin = fd[0];
			}
		}
		if(lexe && check_builtins(lexe->args) == 1)
		{
			id = fork();
			if(id == 0)
			{	
				if(lexe->in == -2 || lexe->in == 0)
					dup2(stdin, 0);
				else
				{
					close(stdin);
					stdin = lexe->in;
					dup2(lexe->in, 0);
				}
				close(stdin);
				if(lexe->out == -2 || lexe->out == 0)	
					dup2(stdout, 1);
				else
				{
					close(stdout);
					stdout = lexe->out;
					dup2(stdout, 1);
				}
				close(stdout);
				close(fd[0]);
				ft_execut_cmnd(lexe, export);
			}
		}
		else if(lexe)
			ft_execut_cmnd(lexe, export);
		if(lexe && lexe->next)
			close(fd[1]);
		close(stdin);
		stdin = save_prev_stdin;
		if(lexe)
			lexe = lexe->next;
	}
	exit_(export, id, lexe1);

	ft_change_exit_st(export, global);
}

