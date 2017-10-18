/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 12:52:13 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/18 16:10:25 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check(t_cmdl *cmdl, int i)
{
	if ((i >= 0 && ft_strstr(cmdl->line.str + i, "||")) || (i == -1 && cmdl->opt
	& COR))
	{
		cmdl->opt &= ~(CPIPE | CAND);
		cmdl->opt |= COR;
		cmdl->line.cur = write(2, "\ncmdor> ", 8) - 1;
		cmdl->line.pr = 7;
	}
	else if ((i >= 0 && ft_strstr(cmdl->line.str + i, "|")) || (i == -1 &&
	cmdl->opt & CPIPE))
	{
		cmdl->opt &= ~(COR | CAND);
		cmdl->opt |= CPIPE;
		cmdl->line.cur = write(2, "\npipe> ", 7) - 1;
		cmdl->line.pr = 6;
	}
	else if ((i >= 0 && ft_strstr(cmdl->line.str + i, "&&")) || (i == -1 &&
	cmdl->opt & CAND))
	{
		cmdl->opt &= ~(CPIPE | COR);
		cmdl->opt |= CAND;
		cmdl->line.cur = write(2, "\ncmdand> ", 9) - 1;
		cmdl->line.pr = 8;
	}
	return (1);
}

static int	check_inhib(char *str, int *i, int mode)
{
	int		j;
	int		count;

	j = *i;
	count = 0;
	while (str[--j] == '\\')
		count++;
	if (!mode && count % 2)
		(*i)++;
	else if (mode && count % 2)
		return (0);
	return (1);
}

static int	look_for_rd(char *str, int i)
{
	int		tmp;

	tmp = i;
	while (tmp--)
	{
		if (((str[tmp] == '<' || str[tmp] == '>') &&
		(str[tmp - (tmp ? 1 : 0)] >= '0' && str[tmp -
		(tmp ? 1 : 0)] <= '9')) && (str[tmp + 1] == '&'))
		{
			tmp--;
			continue ;
		}
		if (str[tmp] != ' ' && str[tmp] != '|' && str[tmp] != '&'
		&& str[tmp] != '<' && str[tmp] != '>' && str[tmp] != ';')
			return (0);
		if ((str[tmp] == '|' || str[tmp] == '&' || str[tmp] == '<' ||
		str[tmp] == '>' || str[tmp] == ';') && check_inhib(str, &tmp, 1))
			break ;
	}
	fd_printf(2, "\n42sh: syntax error near unexpected token `%c%c'",
	str[i], str[i] == str[i + 1] ? str[i + 1] : 0);
	init_cmdl();
	return (1);
}

static int	check_spacing(char *str, int i)
{
	while (str[++i])
		if (str[i] != ' ')
			return (1);
	return (0);
}

int			handle_pipe_and_or(t_cmdl *cmdl, int i)
{
	if (cmdl->opt & (CPIPE | CAND | COR) && !check_spacing(cmdl->line.str, -1))
		return (check(cmdl, -1));
	while (i && cmdl->line.str[i] != '|' && cmdl->line.str[i] != '&')
	{
		if ((cmdl->line.str[i] == '\'' || cmdl->line.str[i] == '\"') &&
		bs(cmdl->line.str, i, cmdl->opt))
			break ;
		i--;
	}
	if ((cmdl->line.str[i] != '|' && cmdl->line.str[i] != '&') ||
	check_spacing(cmdl->line.str, i))
	{
		cmdl->opt &= ~(CPIPE | CAND | COR);
		return (0);
	}
	i -= i && cmdl->line.str[i] == cmdl->line.str[i - 1] ? 1 : 0;
	if (look_for_rd(cmdl->line.str, i))
		return (0);
	if (check_spacing(cmdl->line.str + (i +
		(i && cmdl->line.str[i] == cmdl->line.str[i + 1] ? 2 : 1)), i))
		return (0);
	if (i && cmdl->line.str[i - 1] == '\\')
		check_inhib(cmdl->line.str, &i, 0);
	return (check(cmdl, i));
}
