/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strleft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 14:41:12 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/11 10:49:26 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static char	*find_c(const char *s, char **save, int c)
{
	if (!s || !(*s))
		return (NULL);
	if (*save)
		while (s != *save)
			s++;
	while (*s && *s != (char)c)
		s++;
	if (*s)
	{
		*save = (char *)(&(s) + 1);
		return ((char *)(&(*s)));
	}
	return (NULL);
}

void 			ft_strleft(char **str, int c)
{
	char	*save;
	char	*match;

	save = NULL;
	match = NULL;
	while ((match = find_c(*str, &save, c)))
	{
		while ((*match))
		{
			(*match) = *(match) + 1;
			match++;
		}
	}
}
