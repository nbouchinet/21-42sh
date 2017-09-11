/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:40:50 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:40:58 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static int		ft_isvalid(char *format, int save, int *i)
{
	char	*valid;

	valid = " .0123456789hljz#-+*";
	while (save < (*i))
	{
		if (!ft_strchr(valid, format[save]))
		{
			(*i) = save - 1;
			return (1);
		}
		save += 1;
	}
	return (0);
}

char			ft_findc(char *format, int *i)
{
	int		save;
	char	c;
	char	*conv;

	save = (*i);
	conv = "sSpdDioOuUxXcCbn%@";
	while (format[(*i)])
	{
		if (ft_strchr(conv, format[(*i)]))
		{
			c = format[(*i)];
			if (ft_isvalid(format, save, i) == 0)
				return (c);
			return ('\0');
		}
		(*i)++;
	}
	(*i) = save - 1;
	return ('\0');
}
