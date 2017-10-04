/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 16:19:14 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/25 16:00:26 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	j;

	if (!s)
		return (NULL);
	else
	{
		j = (unsigned int)ft_strlen(s);
		if ((start > j || (start + (unsigned int)len) > j))
			return (NULL);
		else
		{
			if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
				return (NULL);
			else
			{
				ft_strncpy(str, s + start, len);
				str[len] = '\0';
			}
			return (str);
		}
	}
}
