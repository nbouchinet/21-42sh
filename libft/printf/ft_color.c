/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:35:30 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:37:09 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_color(va_list ap, t_b *b, char *format)
{
	char	*rec;

	(void)format;
	b->error = 0;
	rec = va_arg(ap, char*);
	ft_buffill(b, rec);
}
