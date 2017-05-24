/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ulong.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 14:36:55 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 14:05:26 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_putnbr_ulong(unsigned long long int nb)
{
	if (nb > 9)
		ft_putnbr_ulong(nb / 10);
	ft_putchar(nb % 10 + '0');
}
