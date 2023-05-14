/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:19:36 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/09 22:27:08 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_cmnd(t_parsed *lexe, int count, int is_first, t_export **export)
{
	ft_dup(lexe, is_first, count);
	ft_execut_cmnd(lexe, export);
}

void	ft_cmnd_one(t_parsed *lexe, int count, int is_first, t_export **export)
{
	ft_execut_cmnd(lexe, export);
}
