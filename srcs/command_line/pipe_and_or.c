/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 12:52:13 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/11 12:13:58 by zadrien          ###   ########.fr       */
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
		cmdl->opt &= ~(CPIPE | CAND);
		cmdl->opt |= COR;
		return (pipe_and_or(cmdl));
	}
	else if (ft_strstr(cmdl->line.str + i, "|"))
	{
		cmdl->opt &= ~(COR | CAND);
		cmdl->opt |= CPIPE;
		return (pipe_and_or(cmdl));
	}
	else if (ft_strstr(cmdl->line.str + i, "&&"))
	{
		cmdl->opt &= ~(CPIPE | COR);
		cmdl->opt |= CAND;
		return (pipe_and_or(cmdl));
	}
	return (0);
}

static void	check_inhib(char *str, int *i)
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

static int	check_spacing(char *str, int i, int mode)
{
	int		tmp;

	// ft_printf("\nBEGINING: [%c]-[%c]\n", str[i], str[i + 1]);
	tmp = i;
	if (!mode)
	{
		while (tmp--)
		{
			// ft_printf("\n[%c]-[%c]\n", str[tmp], str[tmp + 1]);
			if ((str[tmp] == '<' || str[tmp] == '>') &&
			(str[tmp + 1] == '|' || str[tmp + 1] == '&'))
			{
				// ft_putendl("HELLO");
				continue ;
			}
			if (str[tmp] != ' ' && str[tmp] != '|' && str[tmp] != '&' && str[tmp] != '<' && str[tmp] != '>')
			{
				// ft_putendl("EXITING");
				return (0);
			}
			if (str[tmp] == '|' || str[tmp] == '&' || ((str[tmp] == '<' ||
			str[tmp] == '>')))
			{
				// ft_putendl("WORLD");
				break ;
			}
		}
		fd_printf(2, "\n42sh: syntax error near unexpected token `%c%c'",
		str[i], str[i] == str[i + 1] ? str[i + 1] : 0);
		init_cmdl();
	}
	else
	{
		i = -1;
		while (str[++i])
			if (str[i] != ' ')
				return (1);
		return (0);
	}
	return (1);
}

int			handle_pipe_and_or(t_cmdl *cmdl)
{
	int		i;

	if (cmdl->opt & (CPIPE | CAND | COR) && !check_spacing(cmdl->line.str, 0, 1))
		return (pipe_and_or(cmdl));
	i = ft_strlen(cmdl->line.str) - (ft_strlen(cmdl->line.str) > 0 ? 1 : 0);
	while (i && cmdl->line.str[i] != '|' && cmdl->line.str[i] != '&')
		i--;
	if (!i && cmdl->line.str[i] != '|' && cmdl->line.str[i] != '&')
		return ((cmdl->opt &= ~(CPIPE | CAND | COR)));
	i -= i && cmdl->line.str[i] == cmdl->line.str[i - 1] ? 1 : 0;
	if (check_spacing(cmdl->line.str, i, 0))
		return (0);
	if (check_spacing(cmdl->line.str + (i +
		(i && cmdl->line.str[i] == cmdl->line.str[i + 1] ? 2 : 1)), i, 1))
		return(0);
	if (i && cmdl->line.str[i - 1] == '\\')
		check_inhib(cmdl->line.str, &i);
	return (check(cmdl, i));
}
