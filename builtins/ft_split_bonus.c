/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:55:15 by isbarka           #+#    #+#             */
/*   Updated: 2023/04/27 18:03:09 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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