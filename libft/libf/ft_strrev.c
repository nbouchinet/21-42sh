/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 18:19:03 by zadrien           #+#    #+#             */
/*   Updated: 2017/02/20 14:12:25 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strrev(char *str)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(str);
	s = (char*)malloc(sizeof(char) * i + 1);
	while (i > 0)
	{
		s[j] = str[--i];
		j++;
	}
	s[j] = '\0';
	free(str);
	return (s);
}
