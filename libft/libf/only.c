/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 15:37:41 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/17 15:41:00 by zadrien          ###   ########.fr       */
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
