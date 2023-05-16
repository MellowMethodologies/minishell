/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:16:25 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/16 12:23:18 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	child_do(int *pipefd, t_token *tmp1, t_export *env)
{
	char	*line;

	ft_change_exit_st(&env, 1);
	// signal(SIGINT, heredoc_handle);
	close(pipefd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			continue ;
		}
		if (!ft_strcmp(line, tmp1->value))
		{
			free(line);
			break ;
		}
		if (tmp1->type == WORD)
			ft_putstr_fd(ft_quote_expander(line, env, 0), pipefd[1]);
		else
			ft_putstr_fd(line, pipefd[1]);
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	exit(0);
}

void	heredoc_check(int *pipefd, t_token *tmp1, t_parsed *cmd, t_export *env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		cmd->error_str = "fork error !\n";
		cmd->error = 2;
		return ;
	}
	else if (pid == 0)
		child_do(pipefd, tmp1, env);
	else
	{
		wait(0);
		close(pipefd[1]);
		free(tmp1->value);
		free(tmp1);
		cmd->in = pipefd[0];
		return ;
	}
}

void	heredoc_red(t_parsed *cmd, t_token *tmp, t_export *env)
{
	int			pipefd[2];
	pid_t		pid;
	t_token		*tmp1;
	int			delimiter_type;

	if (tmp->next && (check_arguments(tmp->next->type)))
	{
		tmp1 = tmp->next;
		tmp->next = tmp->next->next;
	}
	if (pipe(pipefd) < 0)
	{
		cmd->error_str = "pipe error!\n";
		cmd->error = 2;
		return ;
	}
	heredoc_check(pipefd, tmp1, cmd, env);
	tmp = tmp->next;
}
