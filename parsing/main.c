/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:59:52 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/04 16:19:16 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int args_count(t_token *lst)
{
	t_token *tmp;
	int i = 0;

	tmp = lst;
	while (tmp)
	{
		if (check_arguments(tmp->type) && tmp->index == 0)
			i++;
		else if (check_arguments(tmp->type) && !check_type(find_node(lst, tmp->index - 1)))
			i++;
		else if (tmp->type == PIPE)
			break;
		tmp = tmp->next;
	}
	return (i);
}

void	args_creation(t_parsed **cmd_ptr, t_token *tmp)
{
	int		i = 0;
	int		args;
	t_token *tmp1;
	t_token *prev;

	tmp1 = tmp;
	args = 0;
	while (tmp)
	{
		if (*cmd_ptr == NULL)
		{
			*cmd_ptr = malloc(sizeof(t_parsed));
			if (*cmd_ptr == NULL)
				return ;
			args = args_count(tmp);
			(*cmd_ptr)->args = ft_calloc(sizeof(char *), (args) + 1);
			if ((*cmd_ptr)->args == NULL)
				return ;
			(*cmd_ptr)->error = 0;
			(*cmd_ptr)->in = -2;
			(*cmd_ptr)->out = -2;
			(*cmd_ptr)->next = NULL;
		}
		if (tmp)
			prev = find_node(tmp1, tmp->index - 1);
		if ((check_arguments(tmp->type) == 1 && (tmp->index == 0 || !prev))
			|| ((check_arguments(tmp->type) == 1) && prev
				&& check_redirection(prev->type) == 0))
			(*cmd_ptr)->args[i++] = ft_strdup(tmp->value);
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
		if ((tmp->type == GREAT || tmp->type == GREATGREAT || tmp->type == LESS)
			&& tmp->next && (tmp->next->type == WORD && tmp->next->value[0] == '$'))
			if (!ft_quote_expander(tmp->next->value, env)
				|| ft_count(ft_quote_expander(tmp->next->value, env), ' ') > 1)
					tmp->next->ambiguous = 1;
		if (tmp && tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			while (tmp && tmp->type == WHITESPACE)
				tmp = tmp->next;
			while (tmp && check_arguments(tmp->type))
				tmp = tmp->next;
		}
		if (tmp && (tmp->type == DOUBLE_QUOTE || tmp->type == WORD))
			tmp->value = ft_quote_expander(tmp->value, env);
		if (tmp)
			tmp = tmp->next;
	}
}

void	check_lex(t_parsed *head, t_token *lex)
{
	t_token		*tmp;
	t_parsed	*tmp1;
	int c;

	tmp = lex;
	tmp1 = head;
	while (tmp1)
	{
		c = 0;
		if (tmp1->error == 1)
		{
			printf("tmp1->error = %d | c %d\n", tmp1->error, c);
			printf("%s", tmp1->error_str);
			break ;
		}
		while (tmp && c == 0)
		{
			if (tmp && tmp->type == GREAT)
				great_red(tmp1, tmp);
			else if (tmp && tmp->type == LESS)
				less_red(tmp1, tmp);
			else if (tmp && tmp->type == GREATGREAT)
				append_red(tmp1, tmp);
			else if (tmp && tmp->type == PIPE)
			{
				if (!tmp->next || (tmp->next && check_redirection(tmp->next->type)))
				{
					tmp1->error_str = "parse error near `|\'\n";
					tmp1->error = 1;
				}
				c = 1;
			}
			else if (tmp1 && tmp1->error == 2)
			{
				c = 1;
			}
			tmp = tmp->next;
		}
		tmp1 = tmp1->next;
	}
}


void *parse(char *str, t_export *env, char **envs)
{
	t_parsed	*cmd;
	t_parsed	*head;
	t_token		*lexe;
	t_token		*tmp;
	t_token		*lex_without_spaces;

	head = NULL;
	cmd = NULL;
	lexe = lexer(str, env);
	indexer(&lexe);
	lex_without_spaces = rm_space(lexe);
	tmp = lex_without_spaces;
	while (tmp)
	{
		if (cmd == NULL)
			args_creation(&cmd, tmp);
		if (tmp && tmp->type == HEREDOC)
			heredoc_red(&cmd, &tmp, env);
		if (tmp && tmp->type == PIPE)
		{
			if (cmd == NULL || tmp->next == NULL)
			{
				ft_putstr_fd("syntax error near `|\n", 2);
				return (NULL);
			}
			add_back_parsed(&head, cmd);
			cmd = NULL;
		}
		if (tmp)
			tmp = tmp->next;
	}
	add_back_parsed(&head, cmd);
	check_lex(head, lex_without_spaces);
	cmd = head;
	// int i;
	// while(cmd)
	// {
	// 	printf("in = %d out = %d\n",cmd->in,cmd->out);
	// 	i = 0;
	// 	while(cmd->args[i])
	// 	{
	// 		printf("{arg = %s}",cmd->args[i]);
	// 		i++;
	// 	}
	// 	cmd = cmd->next;
	// }
	if (cmd)
		cmd->envs = envs;
	return (head);
}

int main(int ac, char **av, char **env)
{
	int			fd[2];
	int			i;
	char		*line;
	t_export	*export;
	t_parsed	*cmd;

	cmd = NULL;
	export = NULL;
	fill_export(&export, env);
	while (1)
	{
		line = readline("minishell> ");
		if (!line || !ft_strcmp(line, "exit"))
			break ;
		add_history(line);
		if (!check_quotes(line))
			continue ;
		cmd = parse(line, export, env);
		ft_execution(cmd, &export, env);
		free(line);
	}
}
