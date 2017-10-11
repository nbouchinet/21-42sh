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
