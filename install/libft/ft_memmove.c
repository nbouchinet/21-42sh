/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 21:46:29 by zadrien           #+#    #+#             */
/*   Updated: 2016/11/21 14:02:12 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;

	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (len)
		{
			len--;
			((unsigned char *)dst)[len] = ((unsigned char*)src)[len];
		}
		return (dst);
	}
	i = 0;
	while (i != len)
	{
		((unsigned char*)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
