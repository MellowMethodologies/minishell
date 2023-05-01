/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:59:39 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/01 11:58:25 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int find_me(char *str, int endquot, int stat)
{
	int i = 0;
	if (stat)
	{
		while (str[endquot])
		{
			if(str[endquot++] == 34)
				return (i);
			i++;
		}
	}
	else
	{
		while (str[endquot])
		{
			if(str[endquot++] == 39)
				return (i);
			i++;
		}
	}
	return(-1);
}

int special(int c)
{
	if (c == 39 || c == 34 || c == '<' \
	|| c == '>' || c == '|' || c == ' ')
		return (1);
	return(0);
}

void check_for_quotes(t_token **lex, char *str, int *i)
{
	int quo;

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

int check_for_specials(t_token **lex, char *str, int *i)
{
	int c;

	c = 0;
	if (str[*i] == '|')
		add_back(lex, ft_lstne("|", PIPE));
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			add_back(lex, ft_lstne(">>", GREATGREAT));
			(*i)++;
		}
		else
			add_back(lex, ft_lstne(">", GREAT));
		}
	else if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			add_back(lex, ft_lstne("<<", HEREDOC));
			c = 1;
			(*i)++;
		}
		else
			add_back(lex, ft_lstne("<", LESS));
	}
	return c;
}

void check_words(t_token **lex,  char *str, int *i, int here)
{
	int	t;
	int	j;
	int	cas;

	j = 0;
	cas = 0;
	t = *i;
	while(str[*i])
	{
		if (((str[*i] == '$' || special(str[*i])) && cas && !here) || (special(str[*i])))
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

void space_it(t_token **lex, char *str, int *i)
{
	if (str[*i] == ' ')
	{
		if (str[*i + 1] == ' ')
		{
			while(str[*i] == ' ')
				(*i)++;
			(*i)--;	
		}
		add_back(lex, ft_lstne(" ", WHITESPACE));
	}
}

t_token* lexer(char *str, t_export *env)
{
	int		i;
	int		c;
	t_token *lex;

	i = 0;
	c = 0;
	lex = NULL;
	while (str[i])
	{
		if (str[i] == ' ')
			space_it(&lex, str, &i);
		else if (str[i] == '$' && str[i + 1] == '$' && !c)
			i += 1;
		else if (str[i] == 34 || str[i] == 39)
			check_for_quotes(&lex, str, &i);
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			c = check_for_specials(&lex, str, &i);
		else if (str[i] && special(str[i]) == 0)
			check_words(&lex, str, &i, c);
		i++;
	}
	ft_expand(lex, env);
	join_word_tokens(lex);
	return (lex);
}
	