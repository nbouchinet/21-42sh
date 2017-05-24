/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:57:35 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/15 15:16:03 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void		ft_free(char ***tab, char **line)
{
	int			i;

	i = -1;
	if ((*line))
	{
		free((*line));
		(*line) = NULL;
	}
	if ( tab)
	{
		while ((*tab)[++i])
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
		free(*tab);
		*tab = NULL;
	}
}
