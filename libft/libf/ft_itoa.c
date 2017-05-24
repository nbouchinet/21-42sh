/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 08:17:13 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 13:59:09 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static char		*itoa_char(int len, int n, int sign)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	if (str)
	{
		str[--len] = '\0';
		while (len--)
		{
			str[len] = '0' + n % 10;
			n /= 10;
		}
		if (sign == 1)
			str[0] = '-';
	}
	return (str);
}

char			*ft_itoa(int n)
{
	int		stock;
	int		len;
	int		sign;

	stock = n;
	len = 2;
	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		sign = 1;
	}
	len += sign;
	while (stock /= 10)
		len++;
	return ((char*)itoa_char(len, n, sign));
}
