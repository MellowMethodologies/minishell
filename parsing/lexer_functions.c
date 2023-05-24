/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:44:53 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/24 15:29:46 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	special(int c)
{
	if (c == 39 || c == 34 || c == '<' \
	|| c == '>' || c == '|' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	check_for_quotes(t_token **lex, char *str, int *i)
{
	int	quo;

	if (str[*i] == '\"')
	{
		quo = find_me(str, *i + 1, 1);
		if (quo > 0)
		{
			add_back(lex, ft_lstne(ft_substr(str, *i + 1, quo), DOUBLE_QUOTE));
			*i += quo + 1;
		}
	}
	else if (str[*i] == '\'')
	{
		quo = find_me(str, *i + 1, 0);
		if (quo > 0)
		{
			add_back(lex, ft_lstne(ft_substr(str, *i + 1, quo), SINGLE_QUOTE));
			*i += quo + 1;
		}
	}
}

int	check_for_specials(t_token **lex, char *str, int *i, int c)
{
	if (str[*i] == '|')
		add_back(lex, ft_lstne(ft_strdup("|"), PIPE));
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			add_back(lex, ft_lstne(ft_strdup(">>"), GREATGREAT));
			(*i)++;
		}
		else
			add_back(lex, ft_lstne(ft_strdup(">"), GREAT));
	}
	else if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			add_back(lex, ft_lstne(ft_strdup("<<"), HEREDOC));
			c = 1;
			(*i)++;
		}
		else
			add_back(lex, ft_lstne(ft_strdup("<"), LESS));
	}
	return (c);
}

void	check_words(t_token **lex, char *str, int *i, int here)
{
	int	t;
	int	j;
	int	cas;

	j = 0;
	cas = 0;
	t = *i;
	while (str[*i])
	{
		if (((str[*i] == '$' || special(str[*i])) && cas && !here)
			|| (special(str[*i])))
		{
			(*i)--;
			break ;
		}
		else
			cas = 1;
		j++;
		(*i)++;
	}
	add_back(lex, ft_lstne(ft_substr(str, t, j), WORD));
}

void	space_it(t_token **lex, char *str, int *i)
{
	if (str[*i] == ' ' || str[*i] == '\t')
	{
		if (str[*i + 1] == ' ' || str[*i + 1] == '\t')
		{
			while (str[*i] == ' ' || str[*i] == '\t')
				(*i)++;
			(*i)--;
		}
		add_back(lex, ft_lstne(" ", WHITESPACE));
	}
}
