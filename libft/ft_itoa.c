/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:19:29 by sbadr             #+#    #+#             */
/*   Updated: 2023/02/18 22:10:33 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_create_str(int i, int j, int n, char *str)
{
	if (n < 0)
	{
		str[j++] = '-';
		n = -n;
	}
	while (n / i > 9)
		i *= 10;
	while (i != 0)
	{
		str[j++] = (n / i) + '0';
		n %= i;
		i /= 10;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	int		j;
	char	*str;

	j = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n <= 0)
		i = 1;
	else
		i = 0;
	while (j != 0)
	{
		i++;
		j /= 10;
	}
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	str = ft_create_str(1, 0, n, str);
	return (str);
}
