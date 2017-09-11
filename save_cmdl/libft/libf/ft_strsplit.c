/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:36:41 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/11 14:47:43 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static int		ft_nbr_words(char const *s, char c)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	if (s[i] == c || s[i] == '\t')
		i++;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\t')
			if (s[i - 1] != c && s[i - 1] != '\t')
				nbr++;
		i++;
		if (s[i] == '\0')
			if (s[i - 1] != c && s[i - 1] != '\t')
				nbr++;
	}
	return (nbr);
}

static char		*ft_strcopy(char const *s, int start, int end, char c)
{
	char	*tab;
	int		i;

	i = 0;
	tab = (char*)malloc(sizeof(char) * (end - start + 1));
	if (tab)
	{
		while (s[start] && s[start] != c && s[start] != '\t')
		{
			tab[i] = s[start];
			i++;
			start++;
		}
		tab[i] = '\0';
		return (tab);
	}
	return (NULL);
}

static char		**split(char const *s, char c, int i)
{
	char	**tab;
	int		start;
	int		end;
	int		j;

	j = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * (ft_nbr_words(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\t'))
			i++;
		start = i;
		if (s[i] != '\0')
		{
			while (s[i] && s[i] != c && s[i] != '\t')
				i++;
			end = i;
			tab[j++] = ft_strcopy(s, start, end, c);
		}
	}
	tab[j] = NULL;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;

	i = 0;
	if (!s || !c)
		return (NULL);
	return (split(s, c, i));
}
