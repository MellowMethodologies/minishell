/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:03:08 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/05 16:04:00 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	great_red(t_parsed *cmd, t_token *tmp)
{
	int	fd;

	if (tmp->next->ambiguous == 1)
	{
		cmd->error_str = "ambiguous redirect\n";
		cmd->error = 1;
		return ;
	}
	fd = open(tmp->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		cmd->error_str = "error opening file\n";
		cmd->error = 1;
		return ;
	}
	cmd->out = fd;
	tmp = tmp->next;
	cmd->error = 0;
}

void	append_red(t_parsed *cmd, t_token *tmp)
{
	int	fd;

	if (tmp->next->ambiguous == 1)
	{
		cmd->error_str = "ambiguous redirect\n";
		cmd->error = 1;
		return ;
	}
	fd = open(tmp->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		cmd->error_str = "error opening file\n";
		cmd->error = 1;
		return ;
	}
	cmd->out = fd;
	tmp = tmp->next;
	cmd->error = 0;
}

void	less_red(t_parsed *cmd, t_token *tmp)
{
	int	fd;

	if (tmp->next->ambiguous == 1)
	{
		cmd->error_str = "ambiguous redirect\n";
		cmd->error = 1;
		return ;
	}
	fd = open(tmp->next->value, O_RDONLY);
	if (fd < 0)
	{
		cmd->error_str = "error opening file\n";
		cmd->error = 1;
		return ;
	}
	cmd->in = fd;
	tmp = tmp->next;
	cmd->error = 0;
}
