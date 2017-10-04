/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:49:49 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/18 18:05:03 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		countword(char *s)
{
	int		i;
	int		w;

	i = 0;
	w = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '\0' && s[i] != '\t' && s[i] != '\v')
		{
			w++;
			while (s[i] != ' ' && s[i] != '\0' && s[i] != '\t' && s[i] != '\v')
				i++;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (w);
}

static int		countletter(char *s, int i)
{
	int		l;

	l = 0;
	while (s[i] != ' ' && s[i] != '\0' && s[i] != '\t' && s[i] != '\v')
	{
		l++;
		i++;
	}
	return (l);
}

static void		*ft_put_word(char *s, int l)
{
	int		i;
	char	*word;

	i = 0;
	word = (char*)malloc(sizeof(char) * (l + 1));
	while (s[i] != ' ' && s[i] != '\0' && s[i] != '\t' && s[i] != '\v')
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char			**ft_split(char const *s)
{
	int		i;
	int		l;
	int		tc;
	char	**tab;

	tc = -1;
	i = countword((char *)s);
	if (!s || i == 0 || !(tab = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '\0' && s[i] != '\t' && s[i] != '\v')
		{
			l = countletter((char *)s, i);
			tab[++tc] = ft_put_word((char *)s + i, l);
			while (s[i] != ' ' && s[i] != '\0' && s[i] != '\t' && s[i] != '\v')
				i++;
		}
		else
			i++;
	}
	tab[++tc] = NULL;
	return (tab);
}
