/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:21:51 by zadrien           #+#    #+#             */
/*   Updated: 2016/11/17 15:03:36 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int	i;
	int	j;

	if (little[0] == '\0')
		return ((char *)big);
	else
	{
		i = 0;
		while (big[i])
		{
			j = 0;
			while (little[j] == big[i + j])
			{
				j++;
				if (little[j] == '\0')
					return ((char *)big + i);
			}
			i++;
		}
		return (0);
	}
}
