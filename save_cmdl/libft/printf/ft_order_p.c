/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:44:07 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:44:15 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_order_p(t_b *b, t_flags flags, char *str, char *rec)
{
	flags.diez = 2;
	if (flags.zer == 1 && flags.isp == 0)
		ft_buffill(b, "0x");
	if (flags.mfw > 0)
		if (!ft_strchr(str, '-'))
			ft_do_mfw(b, flags);
	if (flags.pr > 0)
		ft_do_prec(b, &flags, str);
	if (flags.zer == 0 && flags.isp == 0)
		ft_buffill(b, "0x");
	ft_buffill(b, rec);
	if (flags.mfw > 0)
		if (ft_strchr(str, '-'))
			ft_do_mfw(b, flags);
}
