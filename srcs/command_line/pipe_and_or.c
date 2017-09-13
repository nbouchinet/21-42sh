/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 12:52:13 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/13 09:47:38 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	pipe_and_or(t_cmdl *cmdl)
{
	if (cmdl->opt & CPIPE)
	{
		write(1, "\npipe> ", 7);
		cmdl->line.pr = 7;
		cmdl->line.cur = 7;
	}
	else if (cmdl->opt & CAND)
	{
		write(1, "\ncmdand> ", 9);
		cmdl->line.pr = 9;
		cmdl->line.cur = 9;
	}
	else
	{
		write(1, "\ncmdor> ", 9);
		cmdl->line.pr = 9;
		cmdl->line.cur = 9;
	}
	return (1);
}

static int	bs(char *str, int i)
{
	int		count;

	count = 0;
	while (str[--i] == '\\')
		count++;
	if (count % 2 == 0)
		return (0);
	return (1);
}

static int	check(int k, t_cmdl *cmdl)
{
	ft_printf("\n%s\n", cmdl->line.str + k);
	if (ft_strstr(cmdl->line.str + k, "||"))
	{
		cmdl->opt |= COR;
		return (pipe_and_or(cmdl));
	}
	else if (ft_strstr(cmdl->line.str + k, "|"))
	{
		cmdl->opt |= CPIPE;
		return (pipe_and_or(cmdl));
	}
	else if (ft_strstr(cmdl->line.str + k, "&&"))
	{
		cmdl->opt |= CAND;
		return (pipe_and_or(cmdl));
	}
	return (0);
}

static int	only_space(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' || str[i] != 0)
			return (0);
	return (1);
}

int			handle_pipe_and_or(t_cmdl *cmdl, int k)
{
	int		i;
	char	c;

	i = -1;
	if (cmdl->opt & CCTRLD)
		return (1);
	if ((cmdl->opt & (CPIPE | CAND | COR)) && only_space(cmdl->line.str))
		return (pipe_and_or(cmdl));
	while (cmdl->line.str[++i])
		if ((cmdl->line.str[i] == '|' || cmdl->line.str[i] == '&') &&
		(only_space(cmdl->line.str + i +
		(cmdl->line.str[i + 1] == cmdl->line.str[i] ? 2 : 1))))
			break ;
	if (!cmdl->line.str[i])
		return (0);
	c = cmdl->line.str[i];
	if (cmdl->line.str[i - 1] == '\\' && (k = bs(cmdl->line.str, i)) &&
	cmdl->line.str[i + 1] != c)
		return (0);
	i += k && cmdl->line.str[i - 1] == '\\' ? 1 : 0;
	k = i;
	i += cmdl->line.str[i + 1] == c ? 1 : 0;
	while (cmdl->line.str[++i] && (cmdl->line.str[i] == ' ' ||
	cmdl->line.str[i] == '\\'))
		;
	if ((cmdl->line.str[i] == 0 || cmdl->line.str[i] == '\\') && check(k, cmdl))
		return (1);
	return ((cmdl->opt &= ~(CPIPE | CAND | COR)));
}
