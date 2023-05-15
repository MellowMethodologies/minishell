/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:59:52 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/15 16:19:42 by sbadr            ###   ########.fr       */
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
