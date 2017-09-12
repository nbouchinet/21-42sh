/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whichconv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:46:44 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:46:50 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int		ft_whichconv(va_list ap, t_b *b, char *format, t_ptf *ptf)
{
	int		len;
	int		k;

	len = 1;
	k = 0;
	ptf->c = ft_findc(format, &len);
	if (ptf->c == '\0')
		return (len);
	while (ptf->c != g_tab[k].c && g_tab[k].c != 0)
		k++;
	g_tab[k].ptr(ap, b, format + 1);
	return (len);
}
