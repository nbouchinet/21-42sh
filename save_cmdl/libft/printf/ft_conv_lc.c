/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_lc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:38:08 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:38:11 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static void		ft_mfw_lc(t_b *b, char *str, char *tmp, int nb)
{
	int		i;

	i = 0;
	if (ft_strchr(str, '-'))
	{
		ft_buffill(b, tmp);
		while (i++ < nb)
		{
			if (b->pos == 1023)
				ft_reset(b);
			b->buff[b->pos++] = ' ';
		}
	}
	else
	{
		while (i++ < nb)
		{
			if (b->pos == 1023)
				ft_reset(b);
			b->buff[b->pos++] = ' ';
		}
		ft_buffill(b, tmp);
	}
}

static void		ft_mfw_lc_prepare(t_b *b, char *str, wint_t rec, int nb)
{
	int		i;
	char	nul[2];
	char	*tmp;

	if (rec == 0)
	{
		nul[0] = -1;
		nul[1] = 0;
		tmp = nul;
		b->len += 1;
	}
	else
		tmp = ft_get_wchar(b, rec);
	i = -1;
	while (str[++i] != '\0')
	{
		if (ft_isdigit(str[i]) != 0 && str[i - 1] != '.')
		{
			nb = ft_atoi(&str[i]);
			break ;
		}
	}
	nb -= ft_strlen(tmp);
	b->len += (nb < 0 ? 0 : nb);
	ft_mfw_lc(b, str, tmp, nb);
}

static void		ft_newstr_lc(t_b *b, char *str, va_list ap)
{
	int		nb;
	wint_t	rec;

	nb = 0;
	rec = va_arg(ap, wint_t);
	if (rec > 1114111)
		b->error = 1;
	else
		ft_mfw_lc_prepare(b, str, rec, nb);
}

void			ft_conv_lc(va_list ap, t_b *b, char *format)
{
	int		i;
	char	str[128];

	i = -1;
	b->error = 0;
	while (format[++i] != 'C' && format[i] != 'l' && format[i] != '\0')
		str[i] = format[i];
	str[i] = format[i];
	str[i + 1] = '\0';
	ft_newstr_lc(b, str, ap);
}
