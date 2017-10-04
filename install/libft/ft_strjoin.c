/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 19:33:52 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/25 15:59:54 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	else
	{
		i = ft_strlen(s1) + ft_strlen(s2);
		if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
			return (NULL);
		else
		{
			ft_strcat(str, s1);
			ft_strcat(str, s2);
			str[i] = '\0';
		}
		return (str);
	}
}
