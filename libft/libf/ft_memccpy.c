/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 10:32:11 by zadrien           #+#    #+#             */
/*   Updated: 2017/02/20 14:01:38 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *dst1;
	unsigned char *src1;

	dst1 = (unsigned char*)dst;
	src1 = (unsigned char*)src;
	while (n--)
	{
		*dst1 = *src1;
		if ((unsigned char)c == *src1)
		{
			dst1++;
			return (dst1);
		}
		dst1++;
		src1++;
	}
	return (NULL);
}
