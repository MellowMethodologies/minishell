/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_one_v2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/24 00:33:43 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ignor_lexe(t_parsed **lexe)
{
	(*lexe) = (*lexe)->next;
	unlink("/tmp/b.txt");
	unlink("/tmp/a.txt");
}

void	ft_show_export( t_export **export)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp)
	{
		tmp = tmp->next;
	}
}

int	exit_ww(char *s1, char *s2)
{
	if (s1
		&& (ft_strcmp(s1, "cd") == 0
			|| ft_strcmp(s1, "unset") == 0
			|| ft_strcmp(s1, "exit") == 0
			|| (ft_strcmp(s1, "export") == 0 && s2 != NULL)))
	{
		return (1);
	}
	else
		return (0);
}

void	exit_(t_export **export, pid_t id, t_parsed *lexe1)
{
	t_parsed	*tmp;
	t_parsed	*lexe;
	int			exit;

	tmp = lexe1;
	lexe = lexe1;
	while (tmp->next)
		tmp = tmp->next;
	while (lexe)
	{
		if (id == waitpid(-1, &exit, 0))
		{
			if (WIFEXITED(exit))
			{
				if (exit_ww(tmp->args[0], tmp->args[1]) == 0)
				{
					g_lobal = WEXITSTATUS(exit);
					ft_change_exit_st(export, g_lobal);
				}
			}
		}
		lexe = lexe->next;
	}
}

int	check_builtins(char **strs)
{
	if (ft_strcmp(strs[0], "cd") == 0
		|| ft_strcmp(strs[0], "unset") == 0
		|| ft_strcmp(strs[0], "exit") == 0
		|| (ft_strcmp(strs[0], "export") == 0 && strs[1] != NULL))
		return (0);
	return (1);
}
