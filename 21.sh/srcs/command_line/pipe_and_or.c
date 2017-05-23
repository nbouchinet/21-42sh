/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 17:18:51 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/20 17:19:00 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

extern int g_loop;

static void    pipe_and_or(int i, t_win **win)
{
	g_loop = 1;
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

static void		put_space(char **save)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;

	while ((*save)[++i])
		if ((*save)[i] == '|' || (*save)[i] == '&')
			break ;
	if ((*save)[i + 1] == ' ')
		return ;
	j = (*save)[i + 1] == '|' || (*save)[i] == '&' ? i + 2 : i + 1;
	tmp = ft_strsub((*save), j, ft_strlen(*save) - j);
	(*save)[j] = 0;
	(*save) = ft_strjoinf((*save), " ", 1);
	(*save) = ft_strjoinf((*save), tmp, 1);
}

void	handle_pipe_and_or(char **save, t_win **win)
{
	int		i;
	char	c;

	i = -1;
	while ((*save)[++i])
		if ((*save)[i] == '|' || (*save)[i] == '&')
			break ;
	c = (*save)[i];
	i += (*save)[i + 1] == c ? 1 : 0;
	while ((*save)[++i] == ' ')
		;
	if ((*save)[i] == 0)
	{
		if (ft_strstr((*save), "||"))
				pipe_and_or(2, win);
		else if (ft_strstr((*save), "|"))
				pipe_and_or(1, win);
		else if (ft_strstr((*save), "&&"))
				pipe_and_or(3, win);
		else
			put_space(save);
	}
}