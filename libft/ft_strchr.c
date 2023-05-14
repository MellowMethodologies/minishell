/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:18:39 by sbadr             #+#    #+#             */
/*   Updated: 2022/10/31 14:53:56 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (str[i] == (unsigned char)c)
		return ((char *)str);
	while (str[i++])
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
	return (0);
}
