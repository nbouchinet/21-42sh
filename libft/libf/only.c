/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 15:37:41 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/17 15:41:00 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int		only(char *str, int lower, int upper)
{
	int		i;

	i = -1;
	if (str[0] == 0)
		return (0);
	while (str[++i])
		if (!(str[i] >= lower && str[i] <= upper))
			return (0);
	return (1);
}
