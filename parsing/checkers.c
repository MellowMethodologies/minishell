/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:30:39 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/01 12:03:54 by sbadr            ###   ########.fr       */
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