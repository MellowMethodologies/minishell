/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:59:52 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/02 00:41:48 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	args_count(t_token *lst)
{
	t_token	*tmp;
	int i = 0;

	tmp = lst;
	while (tmp)
	{
		if (check_arguments(tmp-> type) && tmp-> index == 0)
			i++;
		else if (check_arguments(tmp-> type)
			&& !check_type(find_node(lst, tmp -> index - 1)))
				i++;
		else if (tmp-> type == PIPE)
			break ;
		tmp = tmp ->next;
	}
	return (i);
}

void	args_creation(t_parsed **cmd, t_token *tmp)
{
	int i = 1;
	int args;
	t_token *tmp1;
	t_token *prev;
	
	tmp1 = tmp;
	args = 0;

	while (tmp)
	{
		prev = find_node(tmp1, tmp->index -1);
		if ((check_arguments(tmp->type) == 1 && !prev)
			|| ((check_arguments(tmp->type) == 1) && prev
				&& check_redirection(prev->type) == 0))
		{
			if (*cmd == NULL)
			{
				*cmd = malloc(sizeof(t_parsed));
				if (*cmd == NULL)
					return ;
				(*cmd)->cmd = ft_strdup(tmp->value);
				args = args_count(tmp);
				(*cmd)->args = ft_calloc(sizeof(char *), (args) + 1);
				if ((*cmd)->args == NULL)
					return ;
				(*cmd)->args[0] = ft_strdup(tmp->value);
				(*cmd)->in = -2;
				(*cmd)->out = -2;
				(*cmd)->next = NULL;
			}
			else
				(*cmd)->args[i++] = ft_strdup(tmp->value);
		}
		else if (tmp->type == PIPE)
			break ;
		tmp = tmp->next;
	}
}

//the parser part
t_parsed	*check_lex(t_token *lex, t_export *env)
{
	t_parsed	*head = NULL;
	t_parsed	*cmd = NULL;
	t_token		*tmp = lex;
	while (tmp)
	{
		if (cmd == NULL)
			args_creation(&cmd, tmp);
		if (check_redirection(tmp->type)) 
		{
			if (tmp->type == GREAT && !great_red(&cmd, tmp))
				return (NULL);
			else if (tmp->type == LESS && !less_red(&cmd, tmp))
				return (NULL);
			else if (tmp->type == GREATGREAT && !append_red(&cmd, tmp))
				return (NULL);
		}
		if (tmp->type == PIPE)
		{
			if (cmd == NULL || (tmp->next == NULL)) 
			{
				ft_putstr_fd("syntax error near `|\n", 2);
				return (NULL);
			}
			add_back_parsed(&head, cmd);
			cmd = NULL;
		}
		tmp = tmp->next;
	}
	add_back_parsed(&head, cmd);
	return (head);
}

void	ft_expand(t_token *lexe, t_export *env)
{
	t_token		*tmp;

	tmp = lexe;
	while (tmp)
	{
		if ((tmp->type == GREAT || tmp->type == GREATGREAT || tmp->type == LESS)
			&& (tmp->next->type == WORD && tmp->next->value[0] == '$'))
			if (!ft_quote_expander(tmp->next->value, env)
				|| ft_count(ft_quote_expander(tmp->next->value, env), ' ') > 1)
				tmp->next->ambiguous = 1;
		if (tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			while (tmp->type == WHITESPACE)
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

void	*parse(char *str, t_export *env, char **envs)
{
	t_parsed	*cmd;
	t_token		*lexe;
	t_token		*tmp;
	t_token		*lex_without_spaces;

	lexe = lexer(str, env);
	indexer(&lexe);
	lex_without_spaces = rm_space(lexe);
	tmp = lex_without_spaces;
	while (tmp)
	{
		if (tmp->type == HEREDOC && !heredoc_red(&cmd, &tmp, env))
			return (NULL);
		tmp = tmp->next;
	}
	cmd = check_lex(lex_without_spaces, env);
	if (cmd)
		cmd->envs = envs;
	return (cmd);
}

int	main(int ac, char **av, char **env)
{
	int fd[2];
	int i;
	char *line;
	t_export *export;
	export = NULL;
	fill_export(&export, env);
	t_parsed *cmd = NULL;

	while(1)
	{
		line = readline("minishell> ");
		if (!line || !ft_strcmp(line, "exit"))
			break;
		add_history(line);
		if (!check_quotes(line))
			continue ;
		cmd = parse(line, export, env);
		
		ft_execution(cmd, &export, env);	
		// cmd->envs = env;
		// free_parsed(cmd);
		// free(cmd);
		free(line);
		// system("leaks shell");

				// while(cmd)
				// {
				//     free(cmd);
				//     cmd = cmd -> next;
				// }
		
	}
}
