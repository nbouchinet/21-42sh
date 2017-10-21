/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:38:22 by zadrien           #+#    #+#             */
/*   Updated: 2017/02/20 14:12:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*save;

	save = NULL;
	while (*s)
	{
		if (*s == (char)c)
			save = (char*)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char*)s++);
	return (save);
}
