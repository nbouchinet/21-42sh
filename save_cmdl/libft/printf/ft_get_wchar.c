/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:41:06 by khabbar           #+#    #+#             */
/*   Updated: 2017/03/10 09:41:11 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static char				*four_byte(t_b *b, unsigned int lettre, char *str)
{
	char			tmp[5];
	unsigned int	cpy;
	unsigned int	cpy_1;
	unsigned int	cpy_2;

	cpy = lettre;
	cpy_1 = lettre;
	cpy_2 = lettre;
	cpy = cpy << 26;
	cpy = cpy >> 26 | 0b10000000;
	cpy_1 = cpy_1 << 20;
	cpy_1 = cpy_1 >> 26 | 0b10000000;
	cpy_2 = cpy_2 << 14;
	cpy_2 = cpy_2 >> 26 | 0b10000000;
	lettre = lettre << 10;
	lettre = lettre >> 28 | 0b11110000;
	tmp[0] = lettre;
	tmp[1] = cpy_2;
	tmp[2] = cpy_1;
	tmp[3] = cpy;
	tmp[4] = '\0';
	str = tmp;
	b->len += 4;
	return (str);
}

static char				*three_byte(t_b *b, unsigned int lettre, char *str)
{
	char			tmp[4];
	unsigned int	cpy;
	unsigned int	cpy_1;

	cpy = lettre;
	cpy_1 = lettre;
	cpy = cpy << 26;
	cpy = cpy >> 26 | 0b10000000;
	cpy_1 = cpy_1 << 20;
	cpy_1 = cpy_1 >> 26 | 0b10000000;
	lettre = lettre >> 12 | 0b11100000;
	tmp[0] = lettre;
	tmp[1] = cpy_1;
	tmp[2] = cpy;
	tmp[3] = '\0';
	str = tmp;
	b->len += 3;
	return (str);
}

static char				*two_byte(t_b *b, unsigned int lettre, char *str)
{
	char			tmp[3];
	unsigned int	cpy;

	cpy = lettre;
	cpy = cpy >> 6 | 0b11000000;
	lettre = lettre << 26;
	lettre = lettre >> 26 | 0b10000000;
	tmp[0] = cpy;
	tmp[1] = lettre;
	tmp[2] = '\0';
	str = tmp;
	b->len += 2;
	return (str);
}

static char				*one_byte(t_b *b, unsigned int lettre, char *str)
{
	char			tmp[2];

	tmp[0] = lettre;
	tmp[1] = '\0';
	str = tmp;
	b->len += 1;
	return (str);
}

char					*ft_get_wchar(t_b *b, unsigned int lettre)
{
	unsigned int	c;
	int				bits;
	char			*str;

	c = 2147483648;
	bits = 32;
	str = NULL;
	while ((c & lettre) == 0)
	{
		bits--;
		c = c >> 1;
	}
	if (bits <= 7)
		return (one_byte(b, lettre, str));
	if (bits > 7 && bits <= 11)
		return (two_byte(b, lettre, str));
	if (bits > 11 && bits <= 16)
		return (three_byte(b, lettre, str));
	if (bits > 16)
		return (four_byte(b, lettre, str));
	return (str);
}
