/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:37:47 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:37:53 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static void		ft_flags_d(t_b *b, char *str, char *rec, long int nbr)
{
	t_flags				flags;

	flags.pr = 0;
	flags.mfw = 0;
	flags.zer = 0;
	flags.isp = 0;
	flags.min = (nbr < 0 ? 1 : 0);
	flags.pl = (ft_strchr(str, '+') && nbr > -1 ? 1 : 0);
	if ((str[0] == '0') || (str[1] == '0' && !ft_isdigit(str[0]))
	|| (str[2] == '0' && !ft_isdigit(str[1])))
		if (!ft_strchr(str, '-'))
			flags.zer = 1;
	ft_precision(str, &flags);
	if (nbr == 0 && flags.isp == 1)
		rec = "";
	flags.pr -= ft_strlen(rec);
	flags.mfw = ft_mfw(str);
	flags.mfw -= ft_strlen(rec) + flags.min;
	flags.mfw -= (ft_strchr(str, ' ') ? 1 : 0);
	flags.mfw -= (flags.pr > 0 ? flags.pr : 0) + flags.pl;
	b->len += (int)ft_strlen(rec);
	ft_space(b, str, flags, nbr);
	ft_order_d(b, flags, str, rec);
}

static void		ft_newstr_d(t_b *b, char *str, va_list ap)
{
	char				*rec;
	long int			nbr;
	int					i;

	i = -1;
	nbr = 0;
	while (str[++i])
		if (str[i] == 'h')
			nbr += 1;
	if ((ft_strchr(str, 'l')) || (ft_strchr(str, 'j'))
	|| (ft_strchr(str, 'D')) || (ft_strchr(str, 'z')))
		nbr = va_arg(ap, long int);
	else if (nbr == 1)
		nbr = (short)va_arg(ap, int);
	else if (nbr == 2)
		nbr = (char)va_arg(ap, int);
	else
		nbr = va_arg(ap, int);
	ft_itoa_long_nm(&rec, nbr);
	ft_flags_d(b, str, rec, nbr);
}

void			ft_conv_d(va_list ap, t_b *b, char *format)
{
	int					i;
	char				str[128];

	i = -1;
	b->error = 0;
	while (format[++i] != 'd' && format[i] != 'D' && format[i] != 'i'
	&& format[i] != '\0')
		str[i] = format[i];
	str[i] = format[i];
	str[i + 1] = '\0';
	ft_newstr_d(b, str, ap);
}
