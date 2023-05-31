/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/31 01:09:53 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_execution_v4(t_ex_vars *vars, int *fd)
{
	(*vars).stdout_ = fd[1];
	(*vars).save_prev_stdin = fd[0];
}

void	ft_execution_v1(t_parsed *lexe, t_export **ex, t_ex_vars vars, int *fd)
{
	t_parsed	*lexe1;

	lexe1 = lexe;
	while (lexe)
	{
		while (lexe && lexe->args_null == 0)
			ft_execution_v3(&lexe, &vars);
		vars.stdout_ = -1;
		if (lexe && lexe->next)
		{
			if (pipe(fd) != -1)
				ft_execution_v4(&vars, fd);
		}
		ft_execution_v2(lexe, &vars, ex, fd);
		if (lexe && lexe->next)
			close(fd[1]);
		close(vars.stdin_);
		vars.stdin_ = vars.save_prev_stdin;
		if (lexe)
			lexe = lexe->next;
	}
	exit_(ex, vars.id, lexe1);
	unlink("/tmp/ss");
}

void	ft_execution(t_parsed *lexe1, t_export **export)
{
	int			fd[2];
	t_ex_vars	vars;
	t_parsed	*lexe;

	vars.stdin_ = -1;
	vars.save_prev_stdin = -1;
	lexe = lexe1;
	vars.first_lexe = lexe;
	signal(SIGINT, hundle_1);
	signal(SIGQUIT, hundle_2);
	ft_instantiate_export(export);
	ft_execution_v1(lexe, export, vars, fd);
}
