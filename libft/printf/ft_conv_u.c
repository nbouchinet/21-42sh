/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:39:40 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:39:45 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static void		ft_flags_u(t_b *b, char *str, char *rec, long int nbr)
{
	t_flags				flags;

	flags.pr = 0;
	flags.mfw = 0;
	flags.zer = 0;
	flags.isp = 0;
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
	flags.mfw -= ft_strlen(rec);
	flags.mfw -= (flags.pr > 0 ? flags.pr : 0);
	b->len += (int)ft_strlen(rec);
	ft_order_u(b, flags, str, rec);
}

static void		ft_newstr_u(t_b *b, char *str, va_list ap)
{
	char				*rec;
	unsigned long int	nbr;
	int					i;

	i = -1;
	nbr = 0;
	while (str[++i])
		if (str[i] == 'h')
			nbr += 1;
	if ((ft_strchr(str, 'l')) || (ft_strchr(str, 'j'))
	|| (ft_strchr(str, 'U')) || (ft_strchr(str, 'z')))
		nbr = va_arg(ap, unsigned long int);
	else if (nbr == 1)
		nbr = (unsigned short int)va_arg(ap, int);
	else if (nbr == 2)
		nbr = (unsigned char)va_arg(ap, int);
	else
		nbr = va_arg(ap, unsigned int);
	ft_itoa_ulong_nm(&rec, nbr);
	ft_flags_u(b, str, rec, nbr);
}

void			ft_conv_u(va_list ap, t_b *b, char *format)
{
	int					i;
	char				str[128];

	i = -1;
	b->error = 0;
	while (format[++i] != 'u' && format[i] != 'U' && format[i] != '\0')
		str[i] = format[i];
	str[i] = format[i];
	str[i + 1] = '\0';
	ft_newstr_u(b, str, ap);
}
