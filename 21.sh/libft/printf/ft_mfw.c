/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mfw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:43:20 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:43:25 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int		ft_mfw(char *str)
{
	long int	i;
	long int	nb;

	i = 0;
	nb = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) != 0 && str[i - 1] != '.' && str[i] != '0')
		{
			nb = ft_atoi(&str[i]);
			break ;
		}
		i += 1;
	}
	return (nb);
}
