/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:31:03 by sbadr             #+#    #+#             */
/*   Updated: 2022/11/07 12:09:12 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_strchr(set, s1[i]) == '\0')
			break ;
		i++;
	}
	return (i);
}

static int	ft_len(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = ft_start(s1, set);
	j = ft_strlen(s1) - 1;
	while (s1[j])
	{
		if (ft_strrchr(set, s1[j]) == '\0')
			break ;
		j--;
	}
	return (j - i +1);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*s;
	int		len;
	int		t;
	int		i;

	if (!s1 || !set)
		return (0);
	i = ft_start(s1, set);
	t = 0;
	len = ft_len(s1, set);
	if (len > 0)
	{
		s = malloc(len + 1);
		if (!s)
			return (0);
		ft_memcpy(s, s1 + i, len);
		s[len] = '\0';
	}
	else
		s = ft_strdup("");
	return (s);
}
