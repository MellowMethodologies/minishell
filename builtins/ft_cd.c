/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:09:16 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/31 01:08:00 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_setenv(char *variable, char *new_value, t_export **export)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp && ft_strcmp(tmp->variable, variable) != 0)
		tmp = tmp->next;
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(new_value);
	}
	else
	{
		ft_lstadd_back_texport(export,
			ft_lstnew_export(ft_strdup(variable), ft_strdup("")));
	}
}

void	ft_go_home(char *home, t_export **export)
{
	char	cwd[1024];
	char	*oldpwd;

	if (chdir(home) != 0)
	{
		write(2, "error home path\n", 16);
		ft_change_exit_st(export, 1);
		return ;
	}
	oldpwd = getenv("PWD");
	ft_setenv("OLDPWD", oldpwd, export);
	getcwd(cwd, 1024);
	ft_setenv("PWD", cwd, export);
}

void	ft_go_direction(char *dir, t_export **export)
{
	char	cwd[1024];
	char	*oldpwd;

	if (chdir(dir) != 0)
	{
		write(2, "error dir path\n", 15);
		g_lobal = 0;
		ft_change_exit_st(export, 1);
		ft_change_exit_st(export, 1);
		return ;
	}
	oldpwd = getenv("PWD");
	setenv("OLDPWD", oldpwd, 1);
	ft_setenv("OLDPWD", oldpwd, export);
	getcwd(cwd, 1024);
	ft_setenv("PWD", cwd, export);
}

char	*ft_home(t_export **export)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp && ft_strcmp(tmp->variable, "HOME") != 0)
		tmp = tmp->next;
	if (tmp)
		return (tmp->value);
	return (NULL);
}

void	ft_cd(t_parsed *lexe, t_export **export)
{
	char	*home;

	home = ft_home(export);
	if (lexe->args[1] == NULL)
		ft_go_home(home, export);
	else
		ft_go_direction(lexe->args[1], export);
	g_lobal = 0;
}
