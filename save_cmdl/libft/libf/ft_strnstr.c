/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:34:04 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 14:11:57 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static char		*ft_str(const char *s1, const char *to_find, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (s1[i] && i < len)
	{
		while (s1[i + j] == to_find[j] && (i + j < len) && to_find[j])
			j++;
		if (to_find[j] == '\0')
			return ((char*)s1 + i);
		j = 0;
		i++;
	}
	return (NULL);
}

char			*ft_strnstr(const char *s1, const char *to_find, size_t len)
{
	if (ft_strcmp(s1, to_find) == 0)
		return ((char*)s1);
	if (to_find[0] == '\0')
		return ((char*)s1);
	if (!s1 && !to_find)
		return ((char*)(s1));
	return (ft_str(s1, to_find, len));
}
