/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 15:10:53 by zadrien           #+#    #+#             */
/*   Updated: 2016/11/23 15:55:49 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static int		ft_spbeg(char *s)
{
	int		i;

	i = 0;
	while (s[i] == '\n' || s[i] == '\t' || s[i] == ' ')
		i++;
	return (i);
}

static int		ft_spend(char const *s)
{
	int i;

	i = ft_strlen(s) - 1;
	while (s[i] == '\n' || s[i] == '\t' || s[i] == ' ')
		i--;
	return (ft_strlen(s) - i);
}

char			*ft_strtrim(char const *s)
{
	int		i;
	int		nbr;
	int		spend;
	int		spbeg;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	spbeg = ft_spbeg((char*)s);
	spend = ft_spend((char*)s) - 1;
	nbr = (int)ft_strlen((char*)s);
	if (spbeg >= nbr || spend >= nbr)
		return (ft_strdup(""));
	if (!(str = (char*)malloc(sizeof(char) * (nbr - spbeg - spend + 1))))
		return (NULL);
	while ((i + spbeg) != (nbr - spend))
	{
		str[i] = s[spbeg + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
