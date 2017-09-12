/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:15:39 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 14:30:10 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strtrim(char const *s)
{
	char			*s1;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (s)
	{
		len = ft_strlen(s) - 1;
		s1 = (char*)s;
		if (s1[i] == '\0')
			return (ft_strnew(1));
		while ((s1[i] == ' ' || s1[i] == '\n' || s1[i] == '\t') && (s1[i]))
			i++;
		while ((s1[len] == ' ' || s1[len] == '\n' || s1[len] == '\t') && (len))
			len--;
		if (i == ft_strlen(s) && len == 0)
			return (NULL);
		if (len >= i)
			return (ft_strsub(s1, i, len - i + 1));
	}
	return (NULL);
}
