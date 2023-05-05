/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:13:44 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/05 18:50:05 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	check_char_is_exist(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*str_befor_equal(char *str, int there_is_equal)
{
	int		i;
	char	*to_return;
	int		count;

	i = 0;
	count = 0;
	if (there_is_equal == 0)
		return (ft_strdup(str));
	while (str[count] && str[count] != '=' && str[count] != '+')
		count++;
	to_return = malloc(count + 1);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		to_return[i] = str[i];
		i++;
	}
	to_return[i] = '\0';
	return (to_return);
}

void	ft_estantiate_str_after_equal(t_ex_vars **vars)
{
	(*vars) = malloc(sizeof(t_ex_vars));
	(*vars)->start = 0;
	(*vars)->end = 0;
	(*vars)->i = 0;
}

char	*str_after_equal(char *str, int there_is_equal)
{
	t_ex_vars	*vars;
	char		*to_return;

	ft_estantiate_str_after_equal(&vars);
	if (there_is_equal == 0)
		return (NULL);
	while (str[vars->start] && str[vars->start] != '=')
		vars->start = vars->start + 1;
	vars->start = vars->start + 1;
	while (str[vars->end])
		vars->end = vars->end + 1;
	if (vars->end - vars->start == 0)
		return (NULL);
	to_return = malloc(vars->end - vars->start + 1);
	while (str[vars->start])
	{
		to_return[vars->i] = str[vars->start];
		vars->start = vars->start + 1;
		vars->i = vars->i + 1;
	}
	to_return[vars->i] = '\0';
	return (to_return);
}

void fill_export_with_env(t_export *export, t_parsed *lexe)
{
	t_export *tmp;
	export->there_is_equal = check_char_is_exist(lexe->envs[0]);
	export->variable = str_befor_equal(lexe->envs[0], export->there_is_equal);
	export->value = str_after_equal(lexe->envs[0], export->there_is_equal);

	int i = 1;
	export->next = NULL;
	while(lexe->envs[i])
	{
		ft_lstadd_back_texport(&export, ft_lstnew_texport_one());
		tmp = export;
		while(tmp->next)
			tmp = tmp->next;
		tmp->there_is_equal = check_char_is_exist(lexe->envs[i]);
		tmp->variable = str_befor_equal(lexe->envs[i], export->there_is_equal);
		tmp->value = str_after_equal(lexe->envs[i], export->there_is_equal);
		i++;
	}
}

void show_env(t_export **export, t_parsed *lexe)
{
	t_export *tmp = (*export);
	while(tmp)
	{
		if(strcmp(tmp->variable, "?") == 0)
			tmp = tmp->next;
		if(tmp && tmp->there_is_equal == 0)
		{
		}
		else if (tmp && tmp->there_is_equal == 1 && tmp->value == NULL)
		{
			ft_putstr_fd(tmp->variable , 1);
			write(1, "=",2);
			write(1, "\n", 1);
		}
		else if (tmp)
		{
			ft_putstr_fd(tmp->variable , 1);
			ft_putstr_fd("=" , 1);
			ft_putstr_fd(tmp->value , 1);
			write(1, "\n", 1);
		}
		if(tmp)
			tmp = tmp->next;
	}
	exit(0);
}