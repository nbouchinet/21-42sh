/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:11:27 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:53:05 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

static void	count_quotes(char **cmd, t_win **win)
{
	int		i;

	i = -1;
	while ((*cmd)[++i])
	{
		if ((*cmd)[i] == '\'' && !(*win)->quote)
			(*win)->quote = 1;
		else if ((*cmd)[i] == '"' && !(*win)->quote)
			(*win)->quote = i == 0 || (*cmd)[i - 1] != '\\' ? 2 : (*win)->quote;
		else if ((*cmd)[i] == '\'' && (*win)->quote == 1)
			(*win)->quote = 0;
		else if ((*cmd)[i] == '"' && (*win)->quote == 2)
			if (i == 0 || (*cmd)[i - 1] != '\\')
				(*win)->quote = 0;
	}
}

int			check_quotes(char **cmd, t_win **win)
{
	char	tmp[2];

	tmp[0] = 127;
	tmp[1] = 0;
	g_loop = (*cmd) ? g_loop : 0;
	count_quotes(cmd, win);
	if ((*win)->quote == 1 || (*win)->quote == 2)
	{
		(*win)->cur = ((*win)->quote == 1 ? 8 : 9);
		(*cmd) = ft_strjoinf((*cmd), tmp, 1);
		(*win)->quote == 1 ? ft_putstr("\nquote> ") : ft_putstr("\ndquote> ");
	}
	else
		g_loop = 0;
	(*win)->pr = (*win)->quote == 1 ? 8 : 9;
	return (1);
}
