/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmp_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:46:07 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:46:12 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_tmp_ls(t_b *b, char *str, wchar_t *rec)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strchr(str, '.'))
		tmp = "";
	else if (rec == NULL)
	{
		tmp = "(null)";
		b->len += 6;
		ft_buffill(b, tmp);
	}
	else
		while (rec[i] != '\0')
		{
			tmp = ft_get_wchar(b, rec[i]);
			ft_buffill(b, tmp);
			i += 1;
		}
}
