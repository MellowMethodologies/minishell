/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:46:21 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/21 20:24:59 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_quote_expander(char *str, t_export *env, int etat)
{
	char	*res;
	char	*temp;
	int		i;
	int		j;
	int		found_dol;

	i = 0;
	j = 0;
	found_dol = 0;
	res = ft_strdup("");
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

char	*ft_res(char *s1, char *s2, char *var, t_export *env)
{
	char	*result;

	result = ft_strdup(s2);
	free(var);
	free(s1);
	if (env->value)
		free(s2);
	return (result);
}

char	*ft_getenv(char *var, t_export *env)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	if (ft_isdigit(var[i]))
		return (var + 1);
	while (env)
	{
		s1 = ft_strdup(env->variable);
		if (env && env->value)
			s2 = ft_strdup(env->value);
		if (ft_strcmp(s1, var) == 0)
			return (ft_res(s1, s2, var, env));
		free(s1);
		if (env && env->value)
			free(s2);
		env = env->next;
	}
	free(var);
	var = NULL;
	return (ft_strdup(""));
}
