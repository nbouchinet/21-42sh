/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 14:25:21 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/19 13:56:21 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_precision(char *str, t_flags *flags)
{
	long int	i;

	i = -1;
	if (ft_strchr(str, '.'))
	{
		while (str[++i])
			if (str[i] == '.')
			{
				flags->pr = ft_atoi(&str[i + 1]);
				flags->isp = 1;
				break ;
			}
	}
}
