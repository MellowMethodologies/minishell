/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:59:39 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/16 12:14:29 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	find_me(char *str, int endquot, int stat)
{
	int	i;

	i = 0;
	if (stat)
	{
		while (str[endquot])
		{
			if (str[endquot++] == 34)
				return (i);
			i++;
		}
	}
	else
	{
		while (str[endquot])
		{
			if (str[endquot++] == 39)
				return (i);
			i++;
		}
	}
	return (-1);
}

t_token	*lexer_2(char *str, int i, int c, t_token *lex)
{
	while (str[i])
	{
		if (str[i] == ' ')
			space_it(&lex, str, &i);
		else if (str[i] == '$' && str[i + 1] == '$' && !c)
			i += 1;
		else if ((str[i] == 34 && str[i + 1] == 34)
			|| (str[i] == 39 && str[i + 1] == 39))
		{
			add_back(&lex, ft_lstne(ft_strdup(" "), DOUBLE_QUOTE));
			i += 1;
		}
		else if (str[i] == 34 || str[i] == 39)
			check_for_quotes(&lex, str, &i);
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			c = check_for_specials(&lex, str, &i, c);
		else if (str[i] && special(str[i]) == 0)
			check_words(&lex, str, &i, c);
		if (str[i])
			i++;
	}
	return (lex);
}

t_token	*lexer(char *str, t_export *env)
{
	int			i;
	int			c;
	t_token		*lex;

	i = 0;
	c = 0;
	lex = NULL;
	lex = lexer_2(str, i, c, lex);
	free(str);
	str = NULL;
	ft_expand(lex, env);
	join_word_tokens(lex);
	return (lex);
}
