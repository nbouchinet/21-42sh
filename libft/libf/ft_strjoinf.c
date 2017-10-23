/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:00:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/12 17:14:42 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static char	*dupstr(char *s1, char *s2, int w)
{
	if (s1)
	{
		w == 1 ? ft_strdel(&s1) : 0;
		return (ft_strdup(s1));
	}
	else if (s2)
	{
		w == 2 ? ft_strdel(&s2) : 0;
		return (ft_strdup(s2));
	}
	else
		return (NULL);
}

char		*ft_strjoinf(char *s1, char *s2, int w)
{
	char	*str;
	size_t	s1_l;
	size_t	s2_l;

	if (!s1 && !s2)
		return (NULL);
	if ((s1 && !s2) || (!s1 && s2))
		return (dupstr(s1, s2, w));
	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	str = (char*)malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	if (w == 1 && s1)
		ft_strdel(&s1);
	else if (w == 2 && s2)
		ft_strdel(&s2);
	else if (w == 3)
	{
		s1 ? ft_strdel(&s1) : 0;
		s2 ? ft_strdel(&s2) : 0;
	}
	return (str);
}
