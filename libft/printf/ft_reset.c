/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:45:35 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/10 09:45:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_reset(t_b *b)
{
	int		i;

	i = -1;
	while (b->buff[++i])
		if (b->buff[i] == -1)
			b->buff[i] = '\0';
	write(b->fd, b->buff, 1023);
	b->pos = 0;
	i = 0;
	while (i != 1023)
	{
		b->buff[i] = 0;
		i++;
	}
}
