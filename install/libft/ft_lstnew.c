/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 13:50:18 by zadrien           #+#    #+#             */
/*   Updated: 2016/11/20 16:37:52 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*maillon;

	if (!(maillon = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		maillon->content = NULL;
		maillon->content_size = 0;
	}
	else
	{
		if (!(maillon->content = (void*)malloc(sizeof(content))))
			return (NULL);
		if (content == '\0')
			maillon->content = ft_strdup("");
		ft_memcpy(maillon->content, content, content_size);
		maillon->content_size = content_size;
	}
	maillon->next = NULL;
	return (maillon);
}
