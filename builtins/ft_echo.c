/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:11:49 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/21 22:25:10 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_is_n(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	ft_echo_1(int check, t_parsed *lexe, int i, int is_n)
{
	check = 0;
	while (lexe->args[i])
	{
		if (check != 0)
			write(1, " ", 1);
		ft_putstr_fd(lexe->args[i], 1);
		i++;
		check = 1;
	}
	if (!is_n)
		write(1, "\n", 1);
	exit(0);
}

void	ft_echo(t_parsed *lexe)
{
	int	is_n;
	int	i;
	int	check;

	check = 0;
	is_n = 0 ;
	i = 1;
	while (lexe->args[i])
	{
		if (ft_is_n(lexe->args[i]))
		{
			is_n = 1;
			i++;
		}
		else
			break ;
	}
	ft_echo_1(check, lexe, i, is_n);
}
