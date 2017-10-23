/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 08:22:42 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/19 08:45:37 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list		*ptr;
	t_list		*next;

	if (*alst)
	{
		ptr = (*alst);
		while (ptr != NULL)
		{
			next = ptr->next;
			del(ptr->content, ptr->content_size);
			free(ptr);
			ptr = next;
		}
		(*alst) = NULL;
	}
}
