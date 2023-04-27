/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:46:21 by sbadr             #+#    #+#             */
/*   Updated: 2023/04/26 17:49:55 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char *ft_quote_expander(char *str, t_export *env)
{
	char *result = ft_strdup("");
	int i = 0;
	int j = 0;
	int dollar_found = 0;

	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar_found = 1;
			j = i + 1;
			while (ft_isalnum(str[j]) || str[j] == '_')
				j++;
			char *var = ft_substr(str, i, j - i);
			char *value = ft_getenv(1 + var, env);
			if (value)
			{
				char *temp = result;
				result = ft_strjoin(result, ft_substr(str, 0, i));
				free(temp);
				temp = result;
				result = ft_strjoin(result, value);
				free(temp);
				str += j;
				i = -1;
			}
			else
				free(var);
		}
		i++;
	}
	if (dollar_found)
	{
		char *temp = result;
		result = ft_strjoin(result, str);
		free(temp);
	}
	else
	{
		free(result);
		result = ft_strdup(str);
	}
	return (result);
}

char	*ft_getenv(char *var, t_export *env)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	if( ft_isdigit(var[i]))
		return (var + 1);
	while (env)
	{
		s1 = ft_strdup(env->variable);
		s2 = ft_strdup(env->value);
		if (ft_strcmp(s1, var) == 0)
				return (s2);
		free(s1);
		free(s2);
		env = env ->next;
	}
	return ("");
}