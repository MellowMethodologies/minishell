/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_used_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 22:58:52 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/08 21:01:01 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*write_until(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == c)
			break ;
	return (ft_substr(str, 0, i - 1));
}

void	fill_export(t_export **exp, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back_texport(exp, ft_lstnew_export(ft_strdup(write_until(env[i],'=')),
		ft_strdup(1 + ft_strrchr(env[i], '='))));
		i++;
	}
	ft_lstadd_back_texport(exp, ft_lstnew_export("?", "-1"));
}

//calculate how many c is in the str

int	calc_char(char *str, int c)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (str[i])
		if (str[i++] == c)
			sum++;
	return (sum);
}

//check if their is a non ending quote

int	check_quotes(char *line)
{
	int	i;
	int	double_quo;
	int	single_quo;

	i = 0;
	double_quo = calc_char(line, '\'');
	single_quo = calc_char(line, '\"');
	if (double_quo % 2 != 0 || single_quo % 2 != 0)
	{	
		ft_putstr_fd("check quotes\n", 2);
		return (0);
	}
	return (1);
}

//join words and quoted

void	join_word_tokens(t_token *lex)
{
	t_token	*tmp;
	char	*cat;
	t_token	*to_free;

	tmp = lex;
	while (tmp && tmp->next)
	{
		if (check_arguments(tmp->type) && check_arguments(tmp->next->type))
		{
			cat = ft_strjoin(tmp->value, tmp->next->value);
			if (!cat)
				return ;
			free(tmp->value);
			tmp->value = cat;
			tmp->type = WORD;
			to_free = tmp->next;
			tmp->next = tmp->next->next;
			free(to_free);
		}
		else
			tmp = tmp->next;
	}
}
