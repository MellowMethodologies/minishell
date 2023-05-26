/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:46:21 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/26 09:30:21 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

typedef struct s_va
{
	char	*res;
	char	*temp;
	int		i;
	int		j;
	int		found_dol;
}				t_varia;

static void	ft_initiate(t_varia *var)
{
	var->res = ft_strdup("");
	var->temp = NULL;
	var->i = 0;
	var->j = 0;
	var->found_dol = 0;
}

char	*ft_quote_expander(char *str, t_export *env, int etat)
{
	t_varia	var;

	ft_initiate(&var);
	while (str[var.i])
	{
		if (str[var.i] == '$')
		{
			var.i++;
			var.found_dol = 1;
		}
		var.j = var.i;
		var.temp = ft_get_word(str, &var.i);
		if (str[var.i])
			var.i++;
		if (var.found_dol)
			var.temp = ft_getenv(var.temp, env);
		var.res = ft_strjoin1(var.res, var.temp);
		if (var.temp)
			free(var.temp);
		var.found_dol = 0;
	}
	if (etat)
		free(str);
	return (var.res);
}

char	*ft_res(char *s1, char *s2, char *var, t_export *env)
{
	char	*result;

	result = ft_strdup(s2);
	free(var);
	var = NULL;
	free(s1);
	if (env->value)
		free(s2);
	return (result);
}

char	*ft_res_1(char *var)
{
	char	*result;

	result = ft_strdup(var + 1);
	free(var);
	var = NULL;
	return (result);
}

char	*ft_getenv(char *var, t_export *env)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	if (ft_isdigit(var[i]))
		return (ft_res_1(var));
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
