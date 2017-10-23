/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:57:11 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/19 13:56:58 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static void		ft_mfw_c(t_b *b, int n, int neg, va_list ap)
{
	int		i;
	char	c;
	char	tmp[n];

	i = -1;
	c = (char)va_arg(ap, int);
	while (++i < n - 1)
		tmp[i] = ' ';
	tmp[i] = '\0';
	if (neg == 1)
	{
		if (b->pos == 1023)
			ft_reset(b);
		b->buff[b->pos++] = (c == 0 ? -1 : c);
		ft_buffill(b, tmp);
	}
	else
	{
		ft_buffill(b, tmp);
		if (b->pos == 1023)
			ft_reset(b);
		b->buff[b->pos++] = (c == 0 ? -1 : c);
	}
	b->len += n;
}

static void		ft_shortcut_c(int *i, t_b *b, char *str, va_list ap)
{
	while (str[(*i)] != '\0')
	{
		if (ft_isdigit(str[(*i)]) != 0 && str[(*i) - 1] != '.')
		{
			(ft_strchr(str, '-') == NULL ?
			ft_mfw_c(b, ft_atoi(str + (*i)), 0, ap)
			: ft_mfw_c(b, ft_atoi(str + (*i)), 1, ap));
			break ;
		}
		++(*i);
	}
}

void			ft_conv_c(va_list ap, t_b *b, char *format)
{
	int		i;
	char	str[128];

	i = 0;
	b->error = 0;
	while (format[i] != 'c' && format[i] != 'C' && format[i] != 'l'
	&& format[i] != '\0')
	{
		str[i] = format[i];
		++i;
	}
	str[i] = format[i];
	str[i + 1] = '\0';
	if ((ft_strchr(str, 'C')) || (ft_strchr(str, 'l')))
		ft_conv_lc(ap, b, format);
	else
	{
		i = 0;
		ft_shortcut_c(&i, b, str, ap);
		if (str[i] == 0)
			ft_mfw_c(b, 1, 0, ap);
	}
}
