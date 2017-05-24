/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:30:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/17 17:44:29 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bis;

	bis = (unsigned char*)b;
	while (len--)
	{
		*bis = (unsigned char)c;
		bis++;
	}
	return (b);
}
