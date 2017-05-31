/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:43:02 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/31 18:16:37 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	if (n == 0 || !s2)
		return (0);
	i = -1;
	while (s1[++i] && s1[i] == s2[i] && i < n - 1)
		;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
