/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 15:36:18 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 14:08:57 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*s1;
	unsigned int		i;
	int					len;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	s1 = (char*)malloc(sizeof(char) * len + 1);
	if (!s1)
		return (NULL);
	while (s[i])
	{
		s1[i] = f(i, s[i]);
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
