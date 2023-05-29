/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:16:37 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/29 22:14:52 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ambiguous_redirect(t_token	*tmp, t_export *env)
{
	if ((tmp->type == GREAT || tmp->type == GREATGREAT
			|| tmp->type == LESS) && tmp->next)
	{
		while (tmp->next->type == -1)
				tmp = tmp->next;
		if ((tmp->next && tmp->next->value[0] == '$')
			&& (!ft_quote_expander(tmp->next->value, env, 0)[0]
			|| ft_count(ft_quote_expander(tmp->next->\
			value, env, 1), ' ') > 1))
				tmp->next->ambiguous = 1;
	}
}

void	ft_expand(t_token *lexe, t_export *env)
{
	t_token	*tmp;

	tmp = lexe;
	while (tmp)
	{
		ambiguous_redirect(tmp, env);
		if (tmp && tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			while (tmp && tmp->type == WHITESPACE)
				tmp = tmp->next;
			while (tmp && check_arguments(tmp->type))
				tmp = tmp->next;
		}
		if (tmp && (tmp->type == DOUBLE_QUOTE || tmp->type == WORD))
				tmp->value = ft_quote_expander(tmp->value, env, 1);
		if (tmp)
			tmp = tmp->next;
	}
}

void	parsed_filler(t_parsed *cmd, t_token *l, t_parsed **h, t_export *env)
{
	t_token	*tmp;

	tmp = l;
	while (tmp)
	{
		if (cmd == NULL)
			args_creation(&cmd, tmp);
		if (tmp && tmp->type == HEREDOC)
			heredoc_red(cmd, tmp, env);
		if (tmp && tmp->type == PIPE)
		{
			add_back_parsed(h, cmd);
			cmd = NULL;
		}
		if (tmp)
			tmp = tmp->next;
	}
	add_back_parsed(h, cmd);
}

t_parsed	*ft_parse(char *str, t_export *env, t_var *vars)
{
	t_parsed	*head;

	head = NULL;
	if (!str)
	{
		free(str);
		return (head);
	}
	vars->lexe = lexer(str, env);
	if (!check_syntax(vars->lexe))
	{
		free_tokens(&vars->lexe);
		return (head);
	}
	parsed_filler(vars->cmd, vars->lexe, &head, env);
	if (g_lobal == 229)
	{
		g_lobal = 1;
		return (NULL);
	}
	check_lex(head, vars->lexe);
	free_tokens(&vars->lexe);
	return (head);
}

int	args_count(t_token *lst)
{
	t_token	*tmp;
	t_token	*prev;
	int		i;

	prev = NULL;
	i = 0;
	tmp = lst;
	while (tmp)
	{
		prev = find_node(lst, tmp->index - 1);
		if (check_arguments(tmp->type)
			&& !prev)
			i++;
		else if (check_arguments(tmp->type)
			&& (prev && !check_redirection(prev->type)))
				i++;
		else if (tmp->type == PIPE)
			break ;
		tmp = tmp->next;
	}
	return (i);
}
