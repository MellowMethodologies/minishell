/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution__v4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/23 22:49:08 by isbarka          ###   ########.fr       */
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
