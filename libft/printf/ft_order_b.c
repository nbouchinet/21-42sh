/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:43:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:43:38 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_order_b(t_b *b, t_flags flags, char *str, char *rec)
{
	if (flags.mfw > 0)
		if (!ft_strchr(str, '-'))
			ft_do_mfw(b, flags);
	if (flags.pr > 0)
		ft_do_prec(b, &flags, str);
	ft_buffill(b, rec);
	if (flags.mfw > 0)
		if (ft_strchr(str, '-'))
			ft_do_mfw(b, flags);
}
