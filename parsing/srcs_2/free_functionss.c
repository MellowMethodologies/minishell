/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functionss.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 10:51:27 by sbadr             #+#    #+#             */
/*   Updated: 2023/03/27 17:41:23 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void free_args(char **str)
{
    int i;
    i = 0;
    while(str[i])
        free(str[i++]);
    // free(str);
}

void free_parsed(t_parsed *lst)
{
    t_parsed *temp;
    int i = 0;

    while(lst)
    {
        temp = lst->next;
        while (temp->args[i])
            free(temp->args[i++]);
        // free(lst->cmd);
        // free(lst);
        lst = lst->next;
    }
    // free(str);
}

void free_token(t_token *lst)
{
    t_token *temp;

    while(lst)
    {
        temp = lst->next;
        free(lst->value);
        free(lst);
        lst = lst->next;
    }
    // free(str);
}