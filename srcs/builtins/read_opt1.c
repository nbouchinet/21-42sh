/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opt1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:36:37 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/21 17:23:25 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				error_msg(char c)
{
	return (fd_printf(2, "21sh: read: -%c: option requires an argument "
	"read: usage: read [-ers] [-u fd] [-t timeout] [-p prompt]"
	" [-a array] [-n nchars] [-d delim] [name ...]\n", c));
}

int				rtimeout(t_read *var, t_ast **tmp, char *str)
{
	time_t	seconds;

	var->opt |= TR;
	if (*str)
	{
		if (!ft_strdigit(str))
		{
			return (fd_printf(2, "21sh: read: %s: invalid"
			" timeout specification\n", str));
		}
		seconds = ft_atoi(str);
	}
	else if (((*tmp) = (*tmp)->right))
	{
		if (!ft_strdigit((*tmp)->str))
		{
			return (fd_printf(2, "21sh: read: %s: invalid"
			" timeout specification\n", (*tmp)->str));
		}
		seconds = ft_atoi((*tmp)->str);
	}
	else
		return (error_msg('t'));
	var->time = time(NULL);
	return (!(var->endwait = var->time + seconds));
}

int				fd(t_read *var, t_ast **tmp, char *str)
{
	var->opt |= UR;
	if (*str)
	{
		if (!ft_isdigit(str[0]))
		{
			return (fd_printf(2,
			"21sh: read: %s: invalid file"
			"descriptor specification\n", str));
		}
		var->fd = ft_atoi(str);
	}
	else if (((*tmp) = (*tmp)->right))
	{
		if (!ft_isdigit((*tmp)->str[0]))
		{
			return (fd_printf(2,
			"21sh: read: %s: invalid file descriptor specification\n",
			(*tmp)->str));
		}
		var->fd = ft_atoi((*tmp)->str);
	}
	else
		return (error_msg('u'));
	return (0);
}

int				silent(t_read *var, t_ast **tmp, char *str)
{
	(void)var;
	(void)tmp;
	(void)str;
	var->opt |= SR;
	return (0);
}
