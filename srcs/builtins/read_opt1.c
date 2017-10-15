/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opt1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:36:37 by nbouchin          #+#    #+#             */
/*   Updated: 2017/10/11 10:12:54 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				error_msg(char c)
{
	return (fd_printf(2, "42sh: read: -%c: option requires an argument "
	"read: usage: read [-ers] [-u fd] [-t timeout] [-p prompt]"
	" [-a array] [-n nchars] [-d delim] [name ...]\n", c));
}

int				rtimeout(t_read *var, char **arg, int *i, int j)
{
	time_t	seconds;

	var->opt |= TR;
	if (arg[(*i)][j])
	{
		if (!ft_strdigit(&arg[(*i)][j]))
		{
			return (fd_printf(2, "42sh: read: %s: invalid"
			" timeout specification\n", &arg[(*i)][j]));
		}
		seconds = ft_atoi(arg[(*i)] + j);
	}
	else if (arg[(*i) + 1])
	{
		if (!ft_strdigit(&arg[(*i) + 1][0]))
		{
			return (fd_printf(2, "42sh: read: %s: invalid"
			" timeout specification\n", &arg[(*i) + 1]));
		}
		seconds = ft_atoi(arg[++(*i)]);
	}
	else
		return (error_msg('t'));
	var->time = time(NULL);
	return (!(var->endwait = var->time + seconds));
}

int				fd(t_read *var, char **arg, int *i, int j)
{
	var->opt |= UR;
	if (arg[(*i)][j])
	{
		if (!ft_isdigit(arg[(*i)][j]))
		{
			return (fd_printf(2,
			"42sh: read: %s: invalid file"
			"descriptor specification\n", &arg[(*i)][j]));
		}
		var->fd = ft_atoi(arg[(*i)] + j);
	}
	else if (arg[(*i) + 1])
	{
		if (!ft_isdigit(arg[(*i) + 1][0]))
		{
			return (fd_printf(2,
			"42sh: read: %s: invalid file descriptor specification\n",
			&arg[(*i) + 1]));
		}
		var->fd = ft_atoi(arg[++(*i)]);
	}
	else
		return (error_msg('u'));
	return (0);
}

int				silent(t_read *var, char **arg, int *i, int j)
{
	(void)arg;
	(void)i;
	(void)j;
	var->opt |= SR;
	return (0);
}
