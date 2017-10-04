/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:51:56 by zadrien           #+#    #+#             */
/*   Updated: 2016/11/19 21:21:52 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*t;

	s = (unsigned char*)s1;
	t = (unsigned char*)s2;
	i = 0;
	while (i < n)
	{
		if (s[i] != t[i])
			return (s[i] - t[i]);
		i++;
	}
	return (0);
}
