/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iris_west.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:37:13 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/20 16:37:14 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check_save(t_cmdl *cmdl)
{
	int		j;
	char	*str;

	if (cmdl->opt & CPIPE)
		str = ft_strstr(cmdl->line.save, "|") + 1;
	else if (cmdl->opt & CAND)
		str = ft_strstr(cmdl->line.save, "&&") + 2;
	else
		str = ft_strstr(cmdl->line.save, "||") + 2;
	j = -1;
	while (str[++j])
		if (str[j] != ' ')
			return (0);
	return (1);
}

int			iris_west(char *str)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	j = 0;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\')
			++count;
		else if (str[i] != ' ' && str[i] != '\\')
			j = 1;
	}
	if ((count % 2))
		return (1);
	else if (!j && check_save(*cmdl_slg()))
		return (1);
	return (0);
}
