/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:27:56 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 10:39:36 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static int	ft_baselen(long int n, int base)
{
	int		len;

	len = 1;
	while (n /= base)
		len++;
	return (len);
}

char		*ft_itoa_base(long long int n, int base)
{
	char	*result;
	char	str[17];
	int		len;
	int		i;

	len = ft_baselen(n, base);
	i = 1;
	if (base != 10)
	{
		ft_strcpy(str, "0123456789ABCDEF");
		if (!(result = (char*)malloc(sizeof(char) * len)))
			return (NULL);
		while (n != 0)
		{
			result[len - i] = str[(n % base)];
			n /= base;
			i++;
		}
		result[len] = '\0';
	}
	else
		result = ft_itoa(n);
	return (result);
}
