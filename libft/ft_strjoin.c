/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:19:13 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/05 18:52:02 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_error(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*to_return;

	i = 0;
	if (!s1 || !s2)
		return (ft_error(s1, s2));
	to_return = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!to_return)
		return (0);
	while (*s1 != '\0')
	{
		to_return[i] = *s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		to_return[i] = *s2++;
		i++;
	}
	to_return[i] = '\0';
	return (to_return);
}
