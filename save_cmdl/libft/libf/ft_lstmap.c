/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 11:14:30 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 14:00:51 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem))
{
	t_list		*ptr;
	t_list		*next_list;
	t_list		*tmp;
	int			first;

	if (!lst || !f)
		return (NULL);
	next_list = NULL;
	first = 1;
	while (lst)
	{
		ptr = ft_lstnew(f(lst)->content, f(lst)->content_size);
		if (first)
		{
			next_list = ptr;
			tmp = ptr;
			first = 0;
		}
		else
			next_list->next = ptr;
		next_list = ptr;
		lst = lst->next;
	}
	return (tmp);
}
