/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   martha_kent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 19:08:51 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 12:24:17 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		io_number(char *str)
{
	int		i;
	int		j;

	if ((i = ft_strlen(str)) == 1)
	{
		if ((j = ft_atoi(str)) > 0 && j < 9)
			return (1);
	}
	return (0);
}

int		is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int		check_end(char *line)
{
	int		i;

	i = 0;
	while (line[i] && (is_space(line[i]) == 1 || line[i] == '\\'))
	{
		if (line[i] == '\\' && line[i + 1])
			break ;
		i++;
	}
	if (!line[i])
		return (0);
	return (1);
}
