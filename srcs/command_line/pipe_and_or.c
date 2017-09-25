/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 12:52:13 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 12:18:20 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	pipe_and_or(t_cmdl *cmdl)
{
	if (cmdl->opt & CPIPE)
	{
		write(1, "\npipe> ", 7);
		cmdl->line.pr = 6;
		cmdl->line.cur = 6;
	}
	else if (cmdl->opt & CAND)
	{
		write(1, "\ncmdand> ", 9);
		cmdl->line.pr = 8;
		cmdl->line.cur = 8;
	}
	else
	{
		write(1, "\ncmdor> ", 8);
		cmdl->line.pr = 7;
		cmdl->line.cur = 7;
	}
	return (1);
}

static int	check(t_cmdl *cmdl, int i)
{
	if (ft_strstr(cmdl->line.str + i, "||"))
	{
		cmdl->opt |= COR;
		return (pipe_and_or(cmdl));
	}
	else if (ft_strstr(cmdl->line.str + i, "|"))
	{
		cmdl->opt |= CPIPE;
		return (pipe_and_or(cmdl));
	}
	else if (ft_strstr(cmdl->line.str + i, "&&"))
	{
		cmdl->opt |= CAND;
		return (pipe_and_or(cmdl));
	}
	return (0);
}

int			only_space(t_cmdl *cmdl, int limit, int w)
{
	int		i;
	char	*str;

	i = -1;
	str = cmdl->line.str;
	if (!w)
	{
		while (str[++i])
			if (str[i] != ' ')
				return (0);
	}
	else
	{
		while (++i < limit)
			if (str[i] != ' ' && str[i] != 0 && str[i] != '|' && str[i] != '&')
				return (0);
		fd_printf(2, "\n42sh: syntax error near unexpected token `");
		write(2, str + limit - (limit > 0 && str[limit - 1] == str[limit] ?
		1 : 0), (limit > 0 && str[limit - 1] == str[limit] ? 2 : 1));
		write(2, "\'", 1);
		ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
		cmdl->line.save ? ft_strdel(&cmdl->line.save) : 0;
	}
	return (1);
}

static void check_inhib(char *str, int *i)
{
	int		j;
	int		count;

	j = *i;
	count = 0;
	while (str[--j] == '\\')
		count++;
	if (count % 2)
		(*i)++;
}

int			handle_pipe_and_or(t_cmdl *cmdl, int k)
{
	int		i;

	if ((cmdl->opt & (CPIPE | CAND | COR)) && iris_west(cmdl->line.str))
		return (pipe_and_or(cmdl));
	i = ft_strlen(cmdl->line.str);
	while (i && cmdl->line.str[i] != '|' && cmdl->line.str[i] != '&')
	{
		if (cmdl->line.str[i] != ' ' && cmdl->line.str[i] != '|' &&
		cmdl->line.str[i] != '&' && cmdl->line.str[i] != 0)
			k = 1;
		i--;
	}
	if (cmdl->line.str[i] != '|' && cmdl->line.str[i] != '&')
		return (0);
	if (only_space(cmdl, i, 1))
	{
		ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
		return (0);
	}
	i -= (i > 0 && cmdl->line.str[i - 1] == cmdl->line.str[i]) ? 1 : 0;
	if (i > 0 && cmdl->line.str[i - 1] == '\\')
		check_inhib(cmdl->line.str, &i);
	if (!k && check(cmdl, i))
		return (1);
	return ((cmdl->opt &= ~(CPIPE | CAND | COR)));
}
