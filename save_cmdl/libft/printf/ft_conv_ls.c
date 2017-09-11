/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:38:18 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:38:23 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static void		ft_mfw_ls(t_b *b, int nb)
{
	int		i;

	i = 0;
	while (i++ < nb)
	{
		if (b->pos == 1023)
			ft_reset(b);
		b->buff[b->pos++] = ' ';
	}
}

static int		ft_find_nb(char *str, int nb)
{
	int		i;

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
	return (nb);
}

static void		ft_mfw_ls_prepare(t_b *b, char *str, wchar_t *rec, int nb)
{
	nb = ft_find_nb(str, nb);
	if (rec != NULL && !ft_strchr(str, '.'))
		nb -= ft_wstrlen(rec);
	b->len += (nb > 0 ? nb : 0);
	if (!ft_strchr(str, '-') && nb > 0)
		ft_mfw_ls(b, nb);
	ft_tmp_ls(b, str, rec);
	if (ft_strchr(str, '-') && nb > 0)
		ft_mfw_ls(b, nb);
}

static void		ft_newstr_ls(t_b *b, char *str, va_list ap)
{
	int		i;
	int		nb;
	wchar_t	*rec;

	i = -1;
	nb = 0;
	rec = va_arg(ap, wint_t*);
	if (rec != NULL)
		while (rec[++i])
			if (rec[i] > 1114111)
				b->error = 1;
	if (b->error == 0)
		ft_mfw_ls_prepare(b, str, rec, nb);
}

void			ft_conv_ls(va_list ap, t_b *b, char *format)
{
	int		i;
	char	str[128];

	i = -1;
	b->error = 0;
	while (format[++i] != 'S' && format[i] != 'l' && format[i] != '\0')
		str[i] = format[i];
	str[i] = format[i];
	str[i + 1] = '\0';
	ft_newstr_ls(b, str, ap);
}
