/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:37:21 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:37:28 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static void		ft_flags_b(t_b *b, char *str, char *rec)
{
	t_flags				flags;

	flags.pr = 0;
	flags.mfw = 0;
	flags.zer = 0;
	flags.isp = 0;
	flags.pl = 0;
	flags.diez = (ft_strchr(str, '#') ? 2 : 0);
	if ((str[0] == '0') || (str[1] == '0' && !ft_isdigit(str[0]))
	|| (str[2] == '0' && !ft_isdigit(str[1])))
		if (!ft_strchr(str, '-'))
			flags.zer = 1;
	ft_precision(str, &flags);
	flags.pr -= ft_strlen(rec);
	flags.mfw = ft_mfw(str);
	flags.mfw -= ft_strlen(rec) + flags.diez;
	flags.mfw -= (flags.pr > 0 ? flags.pr : 0);
	ft_order_b(b, flags, str, rec);
}

static void		ft_newstr_b(t_b *b, char *str, va_list ap)
{
	char	*rec;

	ft_itoa_base_ulong_nm(&rec, va_arg(ap, unsigned long int), 2);
	b->len += ft_strlen(rec);
	ft_flags_b(b, str, rec);
}

void			ft_conv_b(va_list ap, t_b *b, char *format)
{
	int		i;
	char	str[128];

	i = -1;
	b->error = 0;
	while (format[++i] != 'b' && format[i] != '\0')
		str[i] = format[i];
	str[i] = format[i];
	str[i + 1] = '\0';
	ft_newstr_b(b, str, ap);
}
