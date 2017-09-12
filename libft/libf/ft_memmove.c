/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:07:23 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/17 17:27:26 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst1;
	char	*src1;

	dst1 = (char*)dst;
	src1 = (char*)src;
	if (src1 < dst1)
	{
		dst1 += (len - 1);
		src1 += (len - 1);
		while (len--)
		{
			*dst1 = *src1;
			dst1--;
			src1--;
		}
		return (dst);
	}
	while (len--)
	{
		*dst1 = *src1;
		dst1++;
		src1++;
	}
	return (dst);
}
