/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_check_ed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:33:19 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 18:44:13 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_ed(t_bang *bang, int his_len, int match_len, int w)
{
	if (!w)
	{
		if (bang->n && (bang->n < 0 ? -bang->n : bang->n) > his_len)
			return (fd_printf(2, "\n42sh: !%d: no such event", bang->n));
	}
	else
	{
		if (bang->des != -1 > match_len)
			return (fd_printf(2, "\n42sh: !%d: bad word specifier", bang->des));
		else if ((bang->x > match_len || bang->y > match_len) && bang->y > 0)
			return (fd_printf(2, "\n42sh: !%d-%d: bad word specifier", bang->x,
			bang->y));
		else if ((bang->x > match_len) && bang->y < 0)
			return (fd_printf(2, "\n42sh: !%d-: bad word specifier", bang->x));
	}
	return (0);
}

int		bang_range(t_bang *bang, char *event, char *ptr, int max_arg)
{
	char	**range;

	range = ft_strsplit(event, '-');
	if ((range[0] && (range[0][0] < '0' || range[0][0] > '9')) || (range[1] &&
	(range[1][0] < '0' || range[1][0] > '9')))
	{
		return (fd_printf(2, "\n42sh: %s%@%@: invalid length specifier",
		range[0], range[1] ? "-" : "", range[1] ? range[1] : ""));
	}
	if (ptr && *(ptr + 1) == 0)
	{
		bang->x = ft_atoi(range[0]);
		bang->y = max_arg - 1;
	}
	else if (ptr && ptr == event)
	{
		bang->x = 0;
		bang->y = ft_atoi(range[0]);
	}
	else
	{
		bang->x = ft_atoi(range[0]);
		bang->y = ft_atoi(range[1]);
	}
	return (!(ft_free(range, NULL, 1)));
}

int		bang_error(char *sub, char **opt)
{
	fd_printf(2, "\n42sh: %s: event not found", sub[0] == '^' ? sub : opt[0]);
	ft_free(opt, &sub, 1);
	return (1);
}
