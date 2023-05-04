/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:46:21 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/04 01:33:20 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

// void	completer(char *str, t_var *va, t_export *env)
// {
// 	while (str[va->i])
// 	{
// 		if (str[va->i] == '$')
// 		{
// 			va->dollar_found = 1;
// 			va->j = va->i + 1;
// 			while (ft_isalnum(str[va->j]) || str[va->j] == '_')
// 				va->j++;
// 			va->var = ft_substr(str, va->i, va->j - va->i);
// 			va->value = ft_getenv(1 + va->var, env);
// 			if (va->value)
// 			{
// 				va->temp = va->result;
// 				va->result = ft_strjoin(va->result, ft_substr(str, 0, va->i));
// 				free(va->temp);
// 				va->temp = va->result;
// 				va->result = ft_strjoin(va->result, va->value);
// 				free(va->temp);
// 				str += va->j;
// 				va->i = -1;
// 			}
// 			else
// 				free(va->var);
// 		}
// 		va->i++;
// 	}
// }

// char	*ft_quote_expander(char *str, t_export *env)
// {
// 	t_var	*va;

// 	va = malloc(sizeof(t_var));
// 	va->dollar_found = 0;
// 	va->i = 0;
// 	va->j = 0;
// 	va->result=ft_strdup("");
// 	completer(str, va, env);
// 	if (va->dollar_found)
// 	{
// 		va->temp = va->result;
// 		va->result = ft_strjoin(va->result, str);
// 		free(va->temp);
// 	}
// 	else
// 	{
// 		free(va->result);
// 		va->result = ft_strdup(str);
// 	}
// 	return (va->result);
// }


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
			char *var = ft_substr(str, i, j - i +1);
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
			free(s1);
			free(s2);
			return (result);
		}
		free(s1);
		free(s2);
		env = env->next;
	}
	return (ft_strdup(""));
}

