/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 13:34:50 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/21 17:28:35 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				delim(t_read *var, t_ast **tmp, char *str)
{
	var->opt |= DR;
	if (*str)
		var->delim = ft_strsub(str, 0, 1);
	else if (((*tmp) = (*tmp)->right))
		var->delim = ft_strsub((*tmp)->str, 0, 1);
	else
		return (error_msg('d'));
	return (0);
}

int				nchars(t_read *var, t_ast **tmp, char *str)
{
	var->opt |= NR;
	if (*str)
	{
		if (!ft_isdigit(str[0]))
		{
			return (fd_printf(2, "21sh: read: %s: invalid number\n",
			str));
		}
		var->nchars = ft_atoi(str);
	}
	else if (((*tmp) = (*tmp)->right))
	{
		if (!ft_isdigit((*tmp)->str[0]))
		{
			return (fd_printf(2, "21sh: read: %s: invalid number\n",
			(*tmp)->str));
		}
		var->nchars = ft_atoi((*tmp)->str);
	}
	else
		return (error_msg('n'));
	return (0);
}

int				prompt(t_read *var, t_ast **tmp, char *str)
{
	var->opt |= PR;
	if (*str)
		write(1, str, ft_strlen(str));
	else if (((*tmp) = (*tmp)->right))
		write(1, (*tmp)->str, ft_strlen((*tmp)->str));
	else
		return (error_msg('p'));
	return (0);
}

int				back_slash(t_read *var, t_ast **tmp, char *str)
{
	(void)var;
	(void)tmp;
	(void)str;
	var->opt |= RR;
	return (0);
}
