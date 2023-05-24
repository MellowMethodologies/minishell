/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:06:33 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/24 01:59:12 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	handler(int sig)
{
	(void)sig;
	if (waitpid(-1, NULL, WNOHANG))
	{
		g_lobal = 1;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_handle(int sig)
{
	(void)sig;
	if (waitpid(-1, NULL, WNOHANG))
	{
		exit(-27);
	}
}
