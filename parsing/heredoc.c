/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:16:25 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/08 00:16:09 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void handle(int sig)
{
	exit(1);
}

void	heredoc_red(t_parsed **cmd, t_token **tmp, t_export *env)
{
	int			pipefd[2];
	pid_t		pid;
	char		*line;
	char		*delimiter;
	int			delimiter_type;

	if ((*tmp)->next && (check_arguments((*tmp)->next->type)))
	{
		delimiter = (*tmp)->next->value;
		delimiter_type = (*tmp)->next->type;
		(*tmp)->next = (*tmp)->next->next;
	}
	if (pipe(pipefd) < 0)
	{
		(*cmd)->error_str = "pipe error!\n";
		(*cmd)->error = 2;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		(*cmd)->error_str = "fork error !\n";
		(*cmd)->error = 2;
		return ;
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			signal(SIGINT, handle);
			line = readline("> ");
			if (!ft_strcmp(line, delimiter))
			{
				free(line);
				break ;
			}
			if (delimiter_type == WORD)
				ft_putstr_fd(ft_quote_expander(line, env), pipefd[1]);
			else
				ft_putstr_fd(line, pipefd[1]);
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		wait(0);
		close(pipefd[1]);
		(*cmd)->in = pipefd[0];
		return ;
	}
	(*tmp) = (*tmp)->next;
}
