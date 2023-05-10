/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:16:25 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/10 16:15:12 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	heredoc_red(t_parsed **cmd, t_token **tmp, t_export *env)
{
	int			pipefd[2];
	pid_t		pid;
	t_token	*tmp1;
	char		*line;
	char		*delimiter;
	int			delimiter_type;

	if ((*tmp)->next && (check_arguments((*tmp)->next->type)))
    {
        delimiter = (*tmp)->next->value;
        delimiter_type = (*tmp)->next->type;
        tmp1 = (*tmp)->next;
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
			line = readline("> ");
			if (!ft_strcmp(line, delimiter))
			{
				free(line);
				break ;
			}
			if (delimiter_type == WORD)
				ft_putstr_fd(ft_quote_expander(line, env, 0), pipefd[1]);
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
		free(tmp1->value);
		free(tmp1);
		(*cmd)->in = pipefd[0];
		return ;
	}
	(*tmp) = (*tmp)->next;
}
