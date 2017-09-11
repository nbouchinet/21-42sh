/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 10:03:43 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/28 17:56:28 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_bis;
	unsigned char	*src_bis;

	dst_bis = (unsigned char*)dst;
	src_bis = (unsigned char*)src;
	while (n-- > 0)
	{
		*dst_bis = *src_bis;
		dst_bis++;
		src_bis++;
	}
	return (dst);
}
