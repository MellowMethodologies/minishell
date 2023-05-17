/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:09:16 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/17 01:29:55 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int global;
void	ft_setenv(char *variable, char *new_value, t_export **export)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp && strcmp(tmp->variable, variable) != 0)
		tmp = tmp->next;
	if (tmp)
		tmp->value = ft_strdup(new_value);
}

void	ft_go_home(char *home, t_export **export)
{
	char	cwd[1024];
	char	*oldpwd;

	if (chdir(home) != 0)
	{
		write(2, "error home path", 15);
		exit(1);
	}
	oldpwd = getenv("PWD");
	setenv("OLDPWD", oldpwd, 1);
	ft_setenv("OLDPWD", oldpwd, export);
	getcwd(cwd, 1024);
	setenv("PWD", cwd, 1);
	ft_setenv("PWD", cwd, export);
}

void	ft_go_direction(char *dir, t_export **export)
{
	char	cwd[1024];
	char	*oldpwd;

	if (chdir(dir) != 0)
	{
		write(2, "error dir path", 15);
		global = 0;
		return ;
	}
	oldpwd = getenv("PWD");
	setenv("OLDPWD", oldpwd, 1);
	ft_setenv("OLDPWD", oldpwd, export);
	getcwd(cwd, 1024);
	setenv("PWD", cwd, 1);
	ft_setenv("PWD", cwd, export);
}

char	*ft_home(t_export **export)
{
	t_export	*tmp;

	tmp = (*export);
	while (tmp && strcmp(tmp->variable, "HOME") != 0)
		tmp = tmp->next;
	return (tmp->value);
}

void	ft_cd(t_parsed *lexe, t_export **export)
{
	char	*home;

	home = ft_home(export);
	if (lexe->args[1] == NULL)
		ft_go_home(home, export);
	else
		ft_go_direction(lexe->args[1], export);
	global = 0;
	return ;
}
