/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:46:56 by sbadr             #+#    #+#             */
/*   Updated: 2022/10/31 16:36:06 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long int		lli;

	lli = n;
	if (lli < 0)
	{
		ft_putchar_fd('-', fd);
		lli = -lli;
	}
	if (lli > 9)
	{
		ft_putnbr_fd(lli / 10, fd);
		ft_putchar_fd((lli % 10) + '0', fd);
	}
	else
		ft_putchar_fd(lli + '0', fd);
}	
