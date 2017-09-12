/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:39:17 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:39:22 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static void		ft_mfw_r(t_b *b, int n, int neg, char c)
{
	int		i;

	i = 1;
	if (neg == 1)
	{
		ft_buffill(b, "%");
		while (i++ < n)
		{
			if (b->pos == 1023)
				ft_reset(b);
			b->buff[b->pos++] = ' ';
		}
	}
	else
	{
		while (i++ < n)
		{
			if (b->pos == 1023)
				ft_reset(b);
			b->buff[b->pos++] = c;
		}
		ft_buffill(b, "%");
	}
	b->len += n;
}

static void		ft_shortcut_r(int *i, t_b *b, char c, char *str)
{
	while (str[(*i)] != '\0')
	{
		if (ft_isdigit(str[(*i)]) != 0 && str[(*i) - 1] != '.')
		{
			(ft_strchr(str, '-') == NULL ?
			ft_mfw_r(b, ft_atoi(str + (*i)), 0, c)
			: ft_mfw_r(b, ft_atoi(str + (*i)), 1, c));
			break ;
		}
		++(*i);
	}
}

void			ft_conv_r(va_list ap, t_b *b, char *format)
{
	int		i;
	char	c;
	char	str[512];

	i = -1;
	c = ' ';
	b->error = 0;
	(void)ap;
	while (format[++i] != '%')
		str[i] = format[i];
	str[i] = '%';
	str[i + 1] = '\0';
	i = 0;
	if ((str[0] == '0') || (str[1] == '0'))
	{
		i += (str[1] == 0 ? 2 : 1);
		if (ft_strchr(str, '-') == NULL)
			c = '0';
	}
	ft_shortcut_r(&i, b, c, str);
	if (str[i] == 0)
		ft_mfw_r(b, 1, 0, c);
}
