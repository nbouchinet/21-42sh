/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ulong_nm.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:42:21 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:42:25 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static int		ft_baselen(unsigned long int n, int base)
{
	int		len;

	len = 1;
	while (n != 0)
	{
		len++;
		n /= base;
	}
	return (len);
}

void			ft_itoa_base_ulong_nm(char **rec, unsigned long int n, int base)
{
	char	result[1024];
	char	*str;
	int		len;
	int		i;

	len = ft_baselen(n, base);
	i = 2;
	str = "0123456789abcdefghijklmnopqrstuvwxyz";
	while (n != 0)
	{
		result[len - i] = str[(n % base)];
		n /= base;
		i++;
	}
	result[len - 1] = 0;
	*rec = (result[0] == 0 ? "0\0" : result);
}
