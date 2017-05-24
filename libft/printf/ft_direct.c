/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:40:06 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:40:13 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int		ft_direct(va_list ap, t_b *b, char *format)
{
	int		i;
	t_ptf	ptf;

	i = 0;
	b->error = 0;
	while (format[i])
	{
		if (b->pos == 1023)
			ft_reset(b);
		if (format[i] == '%')
		{
			i += ft_whichconv(ap, b, format + i, &ptf) + 1;
			if (b->error == 1)
				return (-1);
		}
		else
		{
			b->buff[b->pos] = format[i];
			b->pos++;
			b->len++;
			i++;
		}
	}
	return (1);
}
