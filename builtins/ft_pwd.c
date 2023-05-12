/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:02:57 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/09 21:09:58 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_pwd(t_parsed *lexe, t_export **export)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr(1, cwd);
		ft_putstr(1, "\n");
	}
	else
	{
		perror("getcwd() error");
		exit(1);
	}
	exit(0);
}
