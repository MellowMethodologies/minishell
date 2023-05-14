/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:26:40 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/01 12:16:35 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_valid_path(char **paths, char *str)
{
	int	i;

	i = 0;
	if (access(str, X_OK) == 0)
		return (str);
	while (paths[i])
	{
		if (access(ft_strjoin(ft_strjoin(paths[i], "/"), str), X_OK) == 0)
			return (ft_strjoin(ft_strjoin(paths[i], "/"), str));
		i++;
	}
	return (NULL);
}

void	check_error(int x, char *str)
{
	if (x < 0)
	{
		ft_putstr(2, str);
		exit(1);
	}
}
