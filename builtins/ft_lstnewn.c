/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 04:52:28 by isbarka           #+#    #+#             */
/*   Updated: 2023/05/08 22:04:10 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_export	*ft_lstnew_texport(char *str)
{
	t_export	*my_node;

	my_node = malloc(sizeof(t_export));
	if (!my_node)
	{
		return (NULL);
	}
	my_node -> next = NULL;
	my_node -> variable = str;
	return (my_node);
}

t_export	*ft_lstnew_texport_one()
{
	t_export	*my_node;

	my_node = malloc(sizeof(t_export));
	if (!my_node)
	{
		return (NULL);
	}
	my_node -> next = NULL;
	return (my_node);
}