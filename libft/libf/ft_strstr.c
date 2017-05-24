/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:16:26 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 14:12:44 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strstr(const char *s1, const char *to_find)
{
	int		i;
	int		j;

	i = 0;
	if (to_find[0] != '\0')
	{
		while (s1[i])
		{
			j = 0;
			while (to_find[j] == s1[i + j])
			{
				if (to_find[j + 1] == '\0')
					return ((char*)(&s1[i]));
				j++;
			}
			i++;
		}
	}
	else
		return ((char*)(&s1[i]));
	return (NULL);
}
