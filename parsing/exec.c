/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:59:52 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/15 15:56:50 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

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

void	initial_cmd(int args, t_parsed **cmd, t_token *tmp)
{
	*cmd = malloc(sizeof(t_parsed));
	if (*cmd == NULL)
		return ;
	args = args_count(tmp);
	(*cmd)->args = ft_calloc(sizeof(char *), (args) + 1);
	if ((*cmd)->args == NULL)
		return ;
	(*cmd)->error = 0;
	(*cmd)->in = -2;
	(*cmd)->out = -2;
	(*cmd)->next = NULL;
}

void	args_creation(t_parsed **cmd, t_token *tmp)
{
	int		i;
	int		args;
	t_token	*tmp1;
	t_token	*prev;

	tmp1 = tmp;
	args = 0;
	i = 0;
	while (tmp)
	{
		if (*cmd == NULL)
			initial_cmd(args, cmd, tmp);
		if (tmp)
			prev = find_node(tmp1, tmp->index - 1);
		if ((check_arguments(tmp->type) == 1 && (tmp->index == 0 || !prev))
			|| ((check_arguments(tmp->type) == 1) && \
			prev && check_redirection(prev->type) == 0))
			(*cmd)->args[i++] = ft_strdup(tmp->value);
		else if (tmp->type == PIPE)
			break ;
		tmp = tmp->next;
	}
}


void	ft_expand(t_token *lexe, t_export *env)
{
	t_token	*tmp;

	tmp = lexe;
	while (tmp)
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
		str = NULL;
		return (head);
	}
	vars->lexe = lexer(str, env);
	indexer(&vars->lexe);
	rm_space(&vars->lexe);
	if (!check_syntax(vars->lexe))
	{
		free_tokens(&vars->lexe);
		return (head);
	}
	parsed_filler(vars->cmd, vars->lexe, &head, env);
	check_lex(head, vars->lexe);
	free_tokens(&vars->lexe);
	return (head);
}

void	initializer(t_var **vars)
{
	*vars = malloc(sizeof(t_var));

	(*vars)->head = NULL;
	(*vars)->lexe = NULL;
	(*vars)->cmd = NULL;
}

int main(int ac, char **av, char **env)
{
	t_export	*export;
	t_parsed	*cmd;
	t_var		*vars;

	initializer(&vars);
	cmd = NULL;
	export = NULL;
	fill_export(&export, env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		vars->line = readline("minishell> ");
		if (!vars->line)
			break ;
		add_history(vars->line);
		if (!check_quotes(vars->line))
		{
			free(vars->line);
			continue ;
		}
		cmd = ft_parse(vars->line, export, vars);
		if (cmd)
			ft_execution(cmd, &export, env);
		free_parsed(&cmd);
	}
}
