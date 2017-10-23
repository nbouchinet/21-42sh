/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:20:21 by zadrien           #+#    #+#             */
/*   Updated: 2017/02/20 14:06:26 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL || *s == '\0')
		return (NULL);
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return (char*)(&(*s));
	return (NULL);
}
