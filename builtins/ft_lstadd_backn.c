/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_backn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 04:52:05 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/01 12:17:04 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_lstadd_back_texport(t_export **lst, t_export *new)
{
	t_export	*my_lst;

	if (!lst || !new)
		return ;
	my_lst = *lst;
	if (my_lst)
	{
		while (my_lst->next != NULL)
			my_lst = my_lst->next;
		my_lst->next = new;
	}
	else
		*lst = new;
}

void	ft_lstadd_back_tparsed(t_parsed **lst, t_parsed *new)
{
	t_parsed	*my_lst;

	if (!lst || !new)
		return ;
	my_lst = *lst;
	if (my_lst)
	{
		while (my_lst->next != NULL)
			my_lst = my_lst->next;
		my_lst->next = new;
	}
	else
		*lst = new;
}
