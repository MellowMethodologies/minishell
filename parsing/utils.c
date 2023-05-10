/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:46:21 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/10 16:03:24 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_quote_expander(char *str, t_export *env, int etat)
{
	char	*res = ft_strdup("");
	char	*temp;
	int		i = 0;
	int		j = 0;
	int		found_dol = 0;

	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			found_dol = 1;
		}
		j = i;
		while (str[i] && str[i] != '$')
			i++;
		temp = ft_substr(str, j, i);
		if (found_dol)
			temp = ft_getenv(temp, env);
		res = ft_strjoin1(res, temp);
		free(temp);
	}
	if (etat)
		free(str);
	return (res);
}

char	*ft_getenv(char *var, t_export *env)
{
	int		i;
	char	*s1;
	char	*s2;
	char	*result;
	char	**s;

	i = 0;
	if (ft_isdigit(var[i]))
		return (var + 1);
	while (env)
	{
		s1 = ft_strdup(env->variable);
		s2 = ft_strdup(env->value);
		if (ft_strcmp(s1, var) == 0)
		{
			result = ft_strdup(s2);

			if (ft_count(result, ' ') > 1)
				s = ft_split(result, 2);
			free(var);
			free(s1);
			free(s2);
			return (result);
		}
		free(s1);
		free(s2);
		env = env->next;
	}
	free(var);
	return (ft_strdup(""));
}