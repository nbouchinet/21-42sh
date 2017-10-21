/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:36:40 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/28 11:18:41 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	*ft_memalloc(size_t size)
{
	unsigned long	*mem;

	mem = (unsigned long*)malloc(sizeof(unsigned long) * size);
	if (mem)
	{
		ft_memset(mem, 0, size);
		return (mem);
	}
	return (NULL);
}
