/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 04:53:12 by isbarka           #+#    #+#             */
/*   Updated: 2022/10/29 04:53:12 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*new_s;
	int		i;

	i = 0;
	s_len = strlen(s);
	new_s = malloc(s_len + 1);
	if (!new_s)
	{
		return (NULL);
	}
	while (s[i] != '\0')
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
