/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:16:25 by sbadr             #+#    #+#             */
/*   Updated: 2023/04/26 18:07:25 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void handle(int sig)
{
}

int heredoc_red(t_parsed **cmd, t_token **tmp, t_export *env)
{
	int pipefd[2];
	pid_t pid;
	char *delimiter;
	int	delimiter_type;
	t_token *remember;
	if ((*tmp)->next && (check_arguments((*tmp)->next->type)))
	{
		if (!*cmd)
		{
			*cmd = malloc(sizeof(t_parsed));
			(*cmd)->args = NULL;
		}
		if (!(*cmd))
			return (0);
		delimiter = (*tmp)->next->value;
		delimiter_type = (*tmp)->next->type;
		(*tmp)->next = (*tmp)->next->next;
	}
	else if ((*tmp)->next == NULL || !(check_arguments((*tmp)->next-> type)))
	{
			ft_putstr_fd("syntax error near unexpected '<<\n", 2); 
			return (0); 
	}
	if (pipe(pipefd) < 0)
	{
	    ft_putstr_fd("pipe error!\n", 2);
	    return (0);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork error !\n", 2);
		return (0);
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		char *line;
		while (1)
		{
			line = readline("> ");
			signal(SIGQUIT,handle);

			if (!ft_strcmp(line, delimiter))
			{
				free(line);
				break;
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
		waitpid(pid, NULL, 0);
		close(pipefd[1]);
		(*cmd)->in = pipefd[0];
		return (1);
	}
	(*tmp) = (*tmp)->next;
}
