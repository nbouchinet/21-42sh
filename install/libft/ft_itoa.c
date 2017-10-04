/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:33:21 by zadrien           #+#    #+#             */
/*   Updated: 2016/11/19 21:16:57 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static int		ft_countnbr(int n)
{
	int		i;

	i = 1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void		ft_strnbr(char *s, int nbr, int value)
{
	if (value < 0)
	{
		value = -value;
		s[0] = '-';
	}
	while (value >= 10)
	{
		s[nbr] = '0' + (value % 10);
		value = value / 10;
		nbr--;
	}
	s[nbr] = '0' + (value);
}

char			*ft_itoa(int n)
{
	int		nbr;
	int		sign;
	char	*str;

	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr = ft_countnbr(n);
	if (n < 0)
	{
		sign = 1;
		nbr = ft_countnbr(-n);
	}
	if (!(str = (char*)malloc(sizeof(char) * (sign + nbr + 1))))
		return (NULL);
	str[nbr + sign] = '\0';
	ft_strnbr(str, nbr + sign - 1, n);
	return (str);
}
