/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:53:57 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 14:08:16 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

size_t		ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	len_s;
	size_t	len_d;
	size_t	max;

	i = 0;
	len_s = ft_strlen(src);
	len_d = ft_strlen(dst);
	max = size - len_d;
	if (size > len_d)
	{
		while (len_d + i < size - 1)
		{
			dst[i + len_d] = src[i];
			i++;
		}
		dst[i + len_d] = '\0';
		i = len_s + len_d + max;
	}
	return (i < (ft_strlen(dst) + ft_strlen(src))
	? size - len_d + ft_strlen(dst) + ft_strlen(src) : len_s + len_d);
}
