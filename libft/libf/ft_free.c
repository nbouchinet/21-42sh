/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:57:35 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/01 14:37:17 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void		ft_free(char **tab, char **line)
{
	int			i;

	i = -1;
	if (line)
		ft_strdel(line);
	if (tab)
	{
		while (tab[++i])
			ft_strdel(&tab[i]);
		free(tab);
	}
}
