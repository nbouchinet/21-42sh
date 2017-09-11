/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:07:04 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/12 15:51:58 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strdupf(char **src)
{
	char	*dest;

	if (!(*src))
		return (NULL);
	dest = (char*)(malloc(sizeof(char) * (ft_strlen((*src)) + 1)));
	if (dest)
	{
		ft_strcpy(dest, (*src));
		free(*src);
		*src = NULL;
		return (dest);
	}
	return (NULL);
}
