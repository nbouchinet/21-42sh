/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plusminus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:44:50 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/10 09:44:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_plusminus(t_b *b, t_flags flags)
{
	if (flags.pl == 1)
	{
		ft_buffill(b, "+");
		b->len += 1;
	}
	else if (flags.min == 1)
	{
		ft_buffill(b, "-");
		b->len += 1;
	}
}
