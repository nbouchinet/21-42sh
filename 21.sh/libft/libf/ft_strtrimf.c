/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 12:25:10 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/25 12:31:09 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strtrimf(char *s)
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
		{
			s1 = ft_strsub(s1, i, len - i + 1);
			free(s);
			return (s1);
		}
	}
	return (NULL);
}
