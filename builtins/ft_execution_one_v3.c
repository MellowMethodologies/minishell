/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_one_v3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/31 01:14:30 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	hundle_1(int a)
{
	(void)a;
	g_lobal = 131;
}

void	hundle_2(int a)
{
	(void)a;
	g_lobal = 0;
}

void	ft_execution_v5(t_parsed *l, t_ex_vars *v, t_export **export, int *fd)
{
	(*v).id = fork();
	if ((*v).id == 0)
	{	
		if (l->in == -2 || l->in == 0)
			dup2((*v).stdin_, 0);
		else
		{
			close((*v).stdin_);
			(*v).stdin_ = l->in;
			dup2(l->in, 0);
		}
		close((*v).stdin_);
		if (l->out == -2 || l->out == 0)
			dup2((*v).stdout_, 1);
		else
		{
			close((*v).stdout_);
			(*v).stdout_ = l->out;
			dup2((*v).stdout_, 1);
		}
		close((*v).stdout_);
		close(fd[0]);
		ft_execut_cmnd(l, export, &v);
	}
}

void	ft_execution_v2(t_parsed *lexe, t_ex_vars *vars, t_export **ex, int *fd)
{
	if (lexe && check_builtins(lexe->args) == 1)
		ft_execution_v5(lexe, vars, ex, fd);
	else if (lexe)
		ft_execut_cmnd(lexe, ex, &vars);
}

void	ft_execution_v3(t_parsed **lexe, t_ex_vars *vars)
{
	int	ss;

	ss = open("/tmp/ss", O_CREAT | O_RDWR, 0777);
	(*vars).stdin_ = ss;
	(*lexe) = (*lexe)->next;
}
