/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_prec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:40:37 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:40:43 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_do_prec(t_b *b, t_flags *flags, char *str)
{
	long int	i;

	i = -1;
	if (flags->zer == 0 && flags->diez == 2 && flags->nbr == 1)
	{
		(ft_strchr(str, 'X') ? ft_buffill(b, "0X") : ft_buffill(b, "0x"));
		b->len += 2;
		flags->diez = 0;
	}
	while (++i < flags->pr)
	{
		if (b->pos == 1023)
			ft_reset(b);
		b->buff[b->pos++] = '0';
	}
	b->len += flags->pr;
}
