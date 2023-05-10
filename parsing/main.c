/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:59:52 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/10 23:47:25 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	args_count(t_token *lst)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (check_arguments(tmp->type) && tmp->index == 0)
			i++;
		else if (check_arguments(tmp->type)
			&& !check_type(find_node(lst, tmp->index - 1)))
			i++;
		else if (tmp->type == PIPE)
			break ;
		tmp = tmp->next;
	}
	return (i);
}

void	args_creation(t_parsed **cmd, t_token *tmp)
{
	int		i = 0;
	int		args;
	t_token	*tmp1;
	t_token	*prev;

	tmp1 = tmp;
	args = 0;
	while (tmp)
	{
		if (*cmd == NULL)
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

void	check_lex(t_parsed *head, t_token *lex)
{
	t_token		*tmp;
	int			c;

	c = 0;
	tmp = lex;
	if (head->error == 1)
	{
		printf("%s", head->error_str);
		head = head->next;
	}
	while (head)
	{
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
		if (head->error == 2)
		{
			printf("%s", head->error_str);
			break ;
		}
		else if (head->error == 1)
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

void	*parse(char *str, t_export *env, char **envs)
{
	t_parsed	*cmd;
	t_parsed	*head;
	t_token		*lexe;
	t_token		*tmp;

	head = NULL;
	cmd = NULL;
	if (!str)
	{
		free(str);
		str = NULL;
		return (head);
	}
	lexe = lexer(str, env);
	indexer(&lexe);
	rm_space(&lexe);
	if (!check_syntax(lexe))
		return (head);
	tmp = lexe;
	while (tmp)
	{
		if (cmd == NULL)
			args_creation(&cmd, tmp);
		if (tmp && tmp->type == HEREDOC)
			heredoc_red(&cmd, &tmp, env);
		if (tmp && tmp->type == PIPE)
		{
			add_back_parsed(&head, cmd);
			cmd = NULL;
		}
		if (tmp)
			tmp = tmp->next;
	}
	add_back_parsed(&head, cmd);
	check_lex(head, lexe);
	free_tokens(&lexe);
	return (head);
}

void	handler(int sig)
{
	(void)sig;
	if (waitpid(-1, NULL, WNOHANG))
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int main(int ac, char **av, char **env)
{
	int			i;
	char		*line;
	t_export	*export;
	t_parsed	*cmd;

	cmd = NULL;
	export = NULL;
	fill_export(&export, env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		line = readline("minishell> ");
		if (!line)
			break ;
		add_history(line);
		if (!check_quotes(line))
		{
			free(line);
			continue ;
		}
		cmd = parse(line, export, env);
		if (cmd)
			ft_execution(cmd, &export, env);
		free_parsed(&cmd);
	}
}
