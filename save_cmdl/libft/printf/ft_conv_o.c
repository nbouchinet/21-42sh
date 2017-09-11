/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:38:49 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:38:55 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static void		ft_flags_o(t_b *b, char *str, char *rec, unsigned long int nbr)
{
	t_flags				flags;

	flags.pr = 0;
	flags.mfw = 0;
	flags.zer = 0;
	flags.isp = 0;
	flags.pl = 0;
	flags.nbr = (nbr == 0 ? 0 : 1);
	flags.diez = (ft_strchr(str, '#') ? 1 : 0);
	if ((str[0] == '0') || (str[1] == '0' && !ft_isdigit(str[0]))
	|| (str[2] == '0' && !ft_isdigit(str[1])))
		if (!ft_strchr(str, '-'))
			flags.zer = 1;
	ft_precision(str, &flags);
	if (nbr == 0 && flags.diez == 0 && flags.isp == 1)
		rec = "";
	flags.pr -= ft_strlen(rec);
	flags.diez = (ft_strchr(str, '#') ? 1 : 0);
	flags.mfw = ft_mfw(str);
	flags.mfw -= ft_strlen(rec) + flags.diez;
	flags.mfw -= (flags.pr > 0 ? flags.pr : 0);
	b->len += ft_strlen(rec);
	ft_order_o(b, flags, str, rec);
}

static void		ft_newstr_o(t_b *b, char *str, va_list ap)
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
	|| (ft_strchr(str, 'O')) || (ft_strchr(str, 'z')))
		nbr = va_arg(ap, unsigned long int);
	else if (nbr == 1)
		nbr = (unsigned short int)va_arg(ap, int);
	else if (nbr == 2)
		nbr = (unsigned char)va_arg(ap, int);
	else
		nbr = va_arg(ap, unsigned int);
	ft_itoa_base_ulong_nm(&rec, nbr, 8);
	ft_flags_o(b, str, rec, nbr);
}

void			ft_conv_o(va_list ap, t_b *b, char *format)
{
	int					i;
	char				str[128];

	i = -1;
	b->error = 0;
	while (format[++i] != 'o' && format[i] != 'O' && format[i] != '\0')
		str[i] = format[i];
	str[i] = format[i];
	str[i + 1] = '\0';
	ft_newstr_o(b, str, ap);
}
