/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:42:07 by sbadr             #+#    #+#             */
/*   Updated: 2023/03/17 16:03:59 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char const *s, char c)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s == '\0')
			break ;
		n += 1;
		while (*s && *s != c)
			++s;
	}
	return (n);
}

static void	*ft_freeall(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

static char	*ft_allocstr(char const *str, char c)
{
	char	*s;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	s = malloc(sizeof(char) * i + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (1 + ft_count(s, c)));
	if (!arr)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			arr[i] = ft_allocstr(s, c);
			if (!arr[i])
				return (ft_freeall(arr, i));
			i++;
			while (*s && *s != c)
				s++;
		}
		if (*s)
			s++;
	}
	arr[i] = (NULL);
	return (arr);
}
