/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:59:52 by sbadr             #+#    #+#             */
/*   Updated: 2023/04/30 15:59:03 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int args_count(t_token *lst)
{
	t_token *tmp;
	int i = 0;

	tmp = lst;
	while(tmp)
	{
		if (check_arguments(tmp-> type) && tmp-> index == 0)
			i++;
		else if (check_arguments(tmp-> type)
		 &&
		!check_type(find_node(lst, tmp -> index - 1)))
				i++;
		else if (tmp-> type == PIPE)
			break ;
		tmp = tmp ->next;
	}
	return (i);
}

void args_creation(t_parsed **cmd, t_token *tmp)
{
	int i = 1;
	int args;
	t_token *tmp1;
	tmp1 = tmp;
	t_token *prev;
	args = 0;

	while(tmp)
	{
		prev = find_node(tmp1, tmp->index -1);
		if ((check_arguments(tmp->type) == 1 && prev == NULL ) || 
			((check_arguments(tmp->type) == 1 ) && prev != NULL &&
			check_redirection(prev->type) == 0))
		{
			if (*cmd == NULL) 
			{ 
				*cmd = malloc(sizeof(t_parsed)); 
				if (*cmd == NULL) 
					return; 
				(*cmd)->cmd = ft_strdup(tmp->value);
				args = args_count(tmp);
				(*cmd)->args = ft_calloc(sizeof(char*), (args) + 1); 
				if ((*cmd)->args == NULL) 
					return;
				(*cmd)->args[0] = ft_strdup(tmp->value);
				(*cmd)->in = -2; 
				(*cmd)->out = -2;
				(*cmd)->next = NULL;
			}
			else
				(*cmd)->args[i++] = ft_strdup(tmp->value);
		}
		else if (tmp->type == PIPE)
			break;
		tmp = tmp->next;
	}
}

//a checkers
int check_redirection(int c)
{
	if (c == LESS || c == GREAT || c == HEREDOC || c == GREATGREAT)
		return (1);
	return (0); 
}

int check_arguments(int c)
{
	if (c == WORD || c == DOUBLE_QUOTE || c == SINGLE_QUOTE)
		return (1);
	return (0); 
}

//the parser part
t_parsed* check_lex(t_token *lex, t_export *env)
{
	t_parsed *head = NULL;
	t_parsed *cmd = NULL;
	t_token *tmp = lex;
	while (tmp) 
	{
		if (cmd == NULL)
			args_creation(&cmd, tmp);
		if (check(tmp-> type)) 
		{
			if (tmp->type == GREAT && !great_red(&cmd, &tmp))
				return (NULL);
			else if (tmp->type == LESS && !less_red(&cmd, &tmp))
				return (NULL);
			else if (tmp->type == GREATGREAT && !append_red(&cmd, &tmp))
				return (NULL);
		} 
		if (tmp->type == PIPE)
		{   
			if (cmd == NULL || (tmp->next == NULL )) 
			{
				ft_putstr_fd("syntax error near `|\n",2);
				return (NULL);
			}
			add_back_parsed(&head, cmd);
			cmd = NULL;
		}
		tmp = tmp->next;
	}
	add_back_parsed(&head, cmd);
	return head;
}

void *parse(char *str, t_export *env, char **envs)
{
	t_token lex;
	t_parsed *cmd;
	t_token *lexe;
	t_token *tmp;
	t_token *lex_without_spaces;
	t_token **pointer = NULL;
	
	lexe = lexer(str, &lex, env);
	tmp = lexe;
	while(tmp)
	{
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
	join_word_tokens(lexe);
	indexer(&lexe);
	lex_without_spaces = rm_space(lexe);
	tmp = lex_without_spaces;
	while(tmp)
	{
		if (tmp->type == HEREDOC && !heredoc_red(&cmd, &tmp,env))
			return (NULL);
		tmp = tmp->next;
	}
	// free_token(lexe);
	cmd = check_lex(lex_without_spaces, env);
	// if (cmd)
	// 	cmd->envs = envs;
	// free_token(lex_without_spaces);
	return (cmd);
}
void sigint_handler(int sig)
{
    // exit(0);
}

int main(int ac, char **av, char **env)
{
	int fd[2];
	int i;
	char *line;

	t_export *export;
	
	export = NULL;
	fill_export(&export, env);
	t_parsed *cmd = NULL;

	signal(SIGQUIT, sigint_handler);
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
