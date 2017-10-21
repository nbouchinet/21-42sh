/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 14:25:21 by hpelat            #+#    #+#             */
/*   Updated: 2017/03/10 09:45:13 by zadrien          ###   ########.fr       */
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
