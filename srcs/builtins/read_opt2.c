/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 13:34:50 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/15 13:34:59 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				aname(t_read *var, char **arg, int *i, int j)
{
	var->opt |= AR;
	if (arg[(*i)][j])
		var->local = ft_strdup(arg[(*i)] + j);
	else if (arg[(*i) + 1])
		var->local = ft_strdup(arg[++(*i)]);
	else
		return (error_msg('a'));
	return (0);
}

int				delim(t_read *var, char **arg, int *i, int j)
{
	var->opt |= DR;
	if (arg[(*i)][j])
		var->delim = ft_strsub(arg[(*i)], j, 1);
	else if (arg[(*i) + 1])
		var->delim = ft_strsub(arg[++(*i)], 0, 1);
	else
		return (error_msg('d'));
	return (0);
}

int				nchars(t_read *var, char **arg, int *i, int j)
{
	var->opt |= NR;
	if (arg[(*i)][j])
	{
		if (!ft_isdigit(arg[(*i)][j]))
		{
			return (fd_printf(2, "42sh: read: %s: invalid number\n",
			&arg[(*i)][j]));
		}
		var->nchars = ft_atoi(arg[(*i)] + j);
	}
	else if (arg[(*i) + 1])
	{
		if (!ft_isdigit(arg[(*i) + 1][0]))
		{
			return (fd_printf(2, "42sh: read: %s: invalid number\n",
			&arg[(*i) + 1]));
		}
		var->nchars = ft_atoi(arg[++(*i)]);
	}
	else
		return (error_msg('n'));
	return (0);
}

int				prompt(t_read *var, char **arg, int *i, int j)
{
	var->opt |= PR;
	if (arg[(*i)][j])
		write(1, &arg[(*i)][j], ft_strlen(&arg[(*i)][j]));
	else if (arg[(*i) + 1])
		write(1, arg[++(*i)], ft_strlen(arg[(*i)]));
	else
		return (error_msg('n'));
	var->local = ft_strdup("REPLY");
	return (0);
}

int				back_slash(t_read *var, char **arg, int *i, int j)
{
	(void)arg;
	(void)i;
	(void)j;
	var->opt |= RR;
	return (0);
}
