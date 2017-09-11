/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 10:08:57 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 14:01:16 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new;

	new = (t_list*)malloc(sizeof(struct s_list));
	if (!new)
		return (NULL);
	if (content)
	{
		new->content = (void*)malloc(sizeof(content_size));
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
		new->next = NULL;
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
		new->next = NULL;
	}
	return (new);
}
