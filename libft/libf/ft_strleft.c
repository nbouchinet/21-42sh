/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strleft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 14:41:12 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/06 10:53:53 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static char *ft_str_save_chr(const char *s, int c, int reset)
{
	static char		*save = NULL;

	if (reset)
		return ((save = NULL));
	if (!s || *s == '\0' )
		return (NULL);
	if (save)
		while (s != save)
			s++;
	while (*s && *s != (char)c)
		s++;
	if (*s)
	{
		save = (char*)(&(*s) + 1);
		return ((char*)(&(*s)));
	}
	save = NULL;
	return (NULL);
}

void		ft_strleft(char **str, int c)
{
	char	*match;

	while ((match = ft_str_save_chr((*str), c, 0)))
	{
		while (*match)
		{
			(*match) = *(match + 1);
			match++;
		}
	}
	ft_str_save_chr(NULL, 0, 1);
}
