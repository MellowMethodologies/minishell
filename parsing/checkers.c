/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:30:39 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/15 16:02:33 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	check_type(t_token *lex)
{
	if (lex && (lex->type == DOUBLE_QUOTE || lex->type == SINGLE_QUOTE
			|| lex->type == GREATGREAT || lex->type == GREAT
			|| lex->type == HEREDOC || lex->type == LESS))
		return (1);
	else
		return (0);
}

int	check_redirection(int c)
{
	if (c == LESS || c == GREAT || c == HEREDOC || c == GREATGREAT)
		return (1);
	return (0);
}

int	check_arguments(int c)
{
	if (c == WORD || c == DOUBLE_QUOTE || c == SINGLE_QUOTE)
		return (1);
	return (0);
}

void	check_lex_2(t_parsed *head, t_token *lex)
{
	t_token		*tmp;
	int			c;

	c = 0;
	tmp = lex;
	while (tmp && c == 0)
	{
		if (tmp && tmp->type == GREAT)
			great_red(head, tmp);
		else if (tmp && tmp->type == LESS)
			less_red(head, tmp);
		else if (tmp && tmp->type == GREATGREAT)
			append_red(head, tmp);
		else if (tmp && tmp->type == PIPE)
			c = 1;
		tmp = tmp->next;
	}
	c = 0;
}

void	check_lex(t_parsed *head, t_token *lex)
{
	if (head && head->error == 1)
	{
		printf("%s", head->error_str);
		head = head->next;
	}
	while (head)
	{
		check_lex_2(head, lex);
		if (head && head->error == 2)
		{
			printf("%s", head->error_str);
			break ;
		}
		else if (head && head->error == 1)
		{
			printf("%s", head->error_str);
			head = head->next;
			continue ;
		}
		head = head->next;
	}
}

int	check_syntax(t_token *tmp)
{
	t_token	*prev;
	t_token	*lex;

	lex = tmp;
	while (tmp)
	{
		if ((check_redirection(tmp->type) && !tmp->next) \
		|| ((check_redirection(tmp->type) && check_redirection(tmp->next->type))
				|| (check_redirection(tmp->type)
					&& tmp->next->type == PIPE))
			|| (tmp->type == PIPE && ((tmp->index == 0 || !tmp->next)
					|| tmp->next->type == PIPE)))
		{
			ft_putstr_fd("syntax error\n", 2);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
