/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 17:18:51 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:52:38 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

static void		pipe_and_or(int i, t_win **win)
{
	g_loop = 256;
	(*win)->pao = 1;
	if (i == 1)
	{
		ft_putstr("\npipe> ");
		(*win)->pr = 7;
		(*win)->cur = 7;
	}
	else if (i == 2)
	{
		ft_putstr("\ncmdand> ");
		(*win)->pr = 8;
		(*win)->cur = 8;
	}
	else if (i == 3)
	{
		ft_putstr("\ncmdor> ");
		(*win)->pr = 8;
		(*win)->cur = 8;
	}
}

void			handle_pipe_and_or(char **save, t_win **win)
{
	int		i;
	char	c;

	i = -1;
	while ((*save)[++i])
		if ((*save)[i] == '|' || (*save)[i] == '&')
			break ;
	c = (*save)[i];
	i += (*save)[i + 1] == c ? 1 : 0;
	while ((*save)[i++] && ((*save)[i] == ' ' || (*save)[i] == '\\'))
		;
	if ((*save)[i] == '\0' || (*save)[i] == '\\')
	{
		if (ft_strstr((*save), "||"))
			pipe_and_or(2, win);
		else if (ft_strstr((*save), "|"))
			pipe_and_or(1, win);
		else if (ft_strstr((*save), "&&"))
			pipe_and_or(3, win);
		else
			(*win)->pao = 0;
	}
}
