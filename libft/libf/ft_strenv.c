/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 16:17:01 by khabbar           #+#    #+#             */
/*   Updated: 2017/04/05 09:50:52 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strenv(char *big, char *little)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!big)
		return (NULL);
	str = ft_strdup(big);
	while (str[i] != '=' && str[i] != 0)
		i++;
	str[i] = 0;
	if (ft_strcmp(str, little) != 0)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (little);
}
