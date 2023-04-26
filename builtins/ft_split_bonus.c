/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:55:15 by isbarka           #+#    #+#             */
/*   Updated: 2023/02/12 17:51:16 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*my_dest;
	unsigned char	*my_src;
	size_t			i;

	if (n < 0)
		n = ft_strlen(src);
	my_dest = (unsigned char *)dest;
	my_src = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		my_dest[i] = my_src[i];
		i++;
	}
	return (dest);
}

// static char	*ft_word(const char *s, char c)
// {
// 	char	*str;
// 	int		len;

// 	len = word_len(s, c);
// 	str = malloc((len + 1) * sizeof(char));
// 	if (!str)
// 	{
// 		free(str);
// 		return (0);
// 	}
// 	ft_memcpy(str, s, len);
// 	str[len] = '\0';
// 	str = ft_strjoin(str, "/");
// 	return (str);
// }

char	**ft_free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (0);
}