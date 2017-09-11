/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_mfw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:40:23 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:40:28 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_do_mfw(t_b *b, t_flags flags)
{
	long int	i;
	char		c;

	i = -1;
	c = ' ';
	if (flags.isp == 0)
		if (flags.zer == 1)
			c = '0';
	while (++i < flags.mfw)
	{
		if (b->pos == 1023)
			ft_reset(b);
		b->buff[b->pos++] = c;
	}
	b->len += flags.mfw;
}
