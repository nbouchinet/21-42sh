/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 08:22:42 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 14:00:06 by khabbar          ###   ########.fr       */
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
