/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:22:05 by zadrien           #+#    #+#             */
/*   Updated: 2016/11/19 21:07:30 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	else
	{
		while (big[i] && i <= len)
		{
			j = 0;
			while ((big[i + j] == little[j]) && (i + j) < len)
			{
				j++;
				if (little[j] == '\0')
					return ((char *)big + i);
			}
			i++;
		}
	}
	return (0);
}
