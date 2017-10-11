/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 12:25:10 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/11 13:36:00 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	boucle(char *s1, unsigned int *i, unsigned int *len)
{
	while (s1[*i] != '\0' && (s1[*i] == ' ' ||
		s1[*i] == '\n' || s1[*i] == '\t'))
		(*i)++;
	while (*len && (s1[*len] == ' ' || s1[*len] == '\n' || s1[*len] == '\t'))
		(*len)--;
}

char	*ft_strtrimf(char *s)
{
	char			*s1;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	s1 = (char*)s;
	if (s1[i] == '\0')
		return (ft_strnew(1));
	boucle(s1, &i, &len);
	if (i == ft_strlen(s) && len == 0)
	{
		ft_strdel(&s);
		return (NULL);
	}
	else if (len >= i)
	{
		s1 = ft_strsub(s1, i, len - i + 1);
		ft_strdel(&s);
		return (s1);
	}
	return (NULL);
}
