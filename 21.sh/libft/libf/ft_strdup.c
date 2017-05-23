/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:38:59 by khabbar           #+#    #+#             */
/*   Updated: 2017/04/02 12:43:15 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strdup(const char *src)
{
	char	*dest;

	dest = (char*)(malloc(sizeof(char) * (ft_strlen(src) + 1)));
	if (dest)
	{
		ft_strcpy(dest, src);
		return (dest);
	}
	return (NULL);
}
