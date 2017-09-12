/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:45:20 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 10:36:19 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static void		ft_init(t_b *b)
{
	int			i;

	i = 0;
	b->pos = 0;
	b->len = 0;
	while (i != 1023)
	{
		b->buff[i] = '\0';
		i++;
	}
}

int				ft_printf(const char *restrict format, ...)
{
	int			i;
	int			len;
	t_b			b;
	va_list		ap;

	i = -1;
	b.fd = 1;
	va_start(ap, format);
	ft_init(&b);
	ft_direct(ap, &b, (char*)format);
	len = ft_strlen(b.buff);
	if (b.error == 1)
		b.len = -1;
	while (b.buff[++i])
		if (b.buff[i] == -1)
			b.buff[i] = '\0';
	write(1, b.buff, len);
	va_end(ap);
	return (b.len);
}
