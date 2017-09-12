/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:45:48 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:45:52 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_space(t_b *b, char *str, t_flags flags, long int nbr)
{
	if (ft_strchr(str, ' ') && flags.pl == 0 && nbr > -1)
	{
		ft_buffill(b, " ");
		b->len += 1;
	}
}
