/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:45:15 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/31 18:08:45 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		s2 = (char*)malloc(sizeof(char) * (len + 1));
		if (s2)
		{
			while (i < len && s[start])
			{
				s2[i] = s[start];
				i++;
				start++;
			}
			s2[i] = '\0';
			return (s2);
		}
	}
	return (NULL);
}
