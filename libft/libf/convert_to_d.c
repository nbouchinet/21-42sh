/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 12:42:40 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/10 10:17:33 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static int		get_nbr(char *tab)
{
	char		str[2];
	char		lettre[7];
	int			nbr;
	int			i;

	i = 0;
	str[0] = ft_toupper((int)tab[0]);
	str[1] = '\0';
	if ((ft_isalpha(str[0])) == 0)
		nbr = str[0] - '0';
	else
	{
		ft_strcpy(lettre, "ABCDEF");
		nbr = 10;
		while (str[0] != lettre[i])
		{
			nbr++;
			i++;
		}
	}
	return (nbr);
}

int				convert_to_d(char *tab, int base)
{
	char		*point;
	char		*find_x;
	int			result;
	int			len;
	int			i;

	result = 0;
	i = 0;
	find_x = ft_strchr(tab, 'x');
	if (find_x != NULL)
		while (tab[i] != 'x')
			i++;
	point = ((find_x == NULL ? ft_strdup(tab)
				: ft_strsub(tab, i + 1, ft_strlen(tab) - i)));
	len = ft_strlen(point);
	i = -1;
	while (point[++i])
		result += ft_iterative_power(base, --len) * get_nbr(&point[i]);
	return (result);
}
