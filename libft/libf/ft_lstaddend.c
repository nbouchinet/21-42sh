/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:41:07 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/19 13:59:17 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_lstaddend(t_list **list, t_list *new)
{
	if (*list)
	{
		while (*list)
			list = &(*list)->next;
		*list = new;
	}
	else
		*list = new;
}
