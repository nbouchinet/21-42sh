/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:16:31 by zadrien           #+#    #+#             */
/*   Updated: 2016/11/19 21:06:00 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (n == 0)
		return (s1);
	else
	{
		j = ft_strlen(s1);
		while (s2[i] && i < n)
		{
			s1[j + i] = s2[i];
			i++;
		}
		s1[j + i] = '\0';
		return (s1);
	}
}
