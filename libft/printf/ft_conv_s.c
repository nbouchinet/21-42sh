/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:39:29 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:39:33 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static void		ft_mfw_s(t_b *b, char *str, char *tmp, int nb)
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

static void		ft_mfw_s_prepare(t_b *b, char *str, char *rec, int nb)
{
	int		i;
	int		save;
	char	tmp[nb + 1];

	save = nb;
	i = -1;
	while (++i < nb)
		tmp[i] = rec[i];
	tmp[i] = 0;
	nb = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) != 0 && str[i - 1] != '.')
		{
			nb = ft_atoi(&str[i]);
			break ;
		}
		i += 1;
	}
	nb -= save;
	b->len += (nb < 0 ? 0 : nb);
	tmp[save] = '\0';
	ft_mfw_s(b, str, tmp, nb);
}

static void		ft_precision_s(t_b *b, char *str, va_list ap)
{
	int		i;
	int		nb;
	char	*rec;

	i = 0;
	nb = -1;
	rec = va_arg(ap, char*);
	if (rec == NULL)
		rec = "(null)";
	if (ft_strchr(str, '.'))
	{
		while (str[i] != '.')
			i++;
		nb = ft_atoi(&str[i + 1]);
	}
	if ((nb < 0) || (nb > (int)ft_strlen(rec)))
		nb = (int)ft_strlen(rec);
	i = -1;
	b->len += nb;
	ft_mfw_s_prepare(b, str, rec, nb);
}

void			ft_conv_s(va_list ap, t_b *b, char *format)
{
	int		i;
	char	str[512];

	i = -1;
	b->error = 0;
	while (format[++i] != 's' && format[i] != 'S' && format[i] != 'l'
	&& format[i] != '\0')
		str[i] = format[i];
	str[i] = format[i];
	str[i + 1] = '\0';
	if ((ft_strchr(str, 'S')) || (ft_strchr(str, 'l')))
		ft_conv_ls(ap, b, format);
	else
		ft_precision_s(b, str, ap);
}
