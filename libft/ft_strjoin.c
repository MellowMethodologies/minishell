/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:19:13 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/20 13:54:35 by sbadr            ###   ########.fr       */
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
	{
		s2 = ft_strdup("");
		return (ft_strdup(s1));
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*to_return;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (ft_error(s1, s2));
	to_return = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!to_return)
		return (0);
	while (s1[j] != '\0')
		to_return[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		to_return[i++] = s2[j++];
	to_return[i] = '\0';
	return (to_return);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*to_return;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (ft_error(s1, s2));
	to_return = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!to_return)
		return (0);
	while (s1[j] != '\0')
		to_return[i++] = s1[j++];
	j = 0;
	free(s1);
	while (s2[j] != '\0')
		to_return[i++] = s2[j++];
	to_return[i] = '\0';
	return (to_return);
}
