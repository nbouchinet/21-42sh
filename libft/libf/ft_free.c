/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:57:35 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 17:02:24 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int		ft_free(char *tab[], char **line, int w)
{
	int			i;

	i = -1;
	if (w == 2 || w == 3)
		ft_strdel(line);
	if (w == 1 || w == 3)
	{
		if (*tab)
		{
			while (tab[++i])
				tab[i] ? ft_strdel(&tab[i]) : 0;
			free(tab);
		}
	}
	return (1);
}
