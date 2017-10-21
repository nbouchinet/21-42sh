/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:49:33 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 14:43:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	opt_check(int *opt, int bit, int loop, int count)
{
	int		j;

	while (loop--)
	{
		j = loop + 2;
		count = 0;
		while (j--)
			count += (*opt & (bit << j)) ? 1 : 0;
		if (count > 1)
			return (fd_printf(2, "history: cannot use "
			"more than one of -anrw\n"));
		bit += bit;
	}
	return (0);
}

static int	get_offset(t_ast *tmp, char *str, int *offset)
{
	int		ret;

	ret = 1;
	if (*(str + 1) && (ret == only(str + 1, '0', '9')))
		*offset = ft_atoi(str + 1);
	else if (*(str + 1) && !ret)
		return (fd_printf(2, "42sh: history: -d: %s "
		"history position out of range\n", str + 1));
	else if (tmp->right && (ret = (only(tmp->right->str, '0', '9'))))
		*offset = ft_atoi(tmp->right->str);
	else if (tmp->right && !ret)
		return (fd_printf(2, "42sh: history: -d: %s "
		"history position out of range\n", tmp->right->str));
	else
		return (fd_printf(2, "42sh: history: -d: option "
		"requires an argument\n"));
	return (0);
}

static int	options(t_ast *tmp, int *opt, int *offset)
{
	char	*str;

	str = tmp->str + 1;
	while (*str)
	{
		if (!ft_strchr("cdanrwps", *str))
			return (fd_printf(2, "history: -%c: %s\n%s%s", *str, HO, HU1, HU2));
		if (*str == 'd' && (*opt |= D) && get_offset(tmp, str, offset))
			return (1);
		else if (*str == 'd' && (*opt |= D))
			break ;
		*str == 'c' ? (*opt) |= C : 0;
		*str == 'a' ? (*opt) |= A : 0;
		*str == 'n' ? (*opt) |= N : 0;
		*str == 'r' ? (*opt) |= R : 0;
		*str == 'w' ? (*opt) |= W : 0;
		*str == 'p' ? (*opt) |= P : 0;
		if (*str == 's' && (*opt |= S))
			return (0);
		str++;
	}
	if (opt_check(opt, 4, 3, 0))
		return (1);
	return (0);
}

static int	parse_opt(t_ast **ast, char **arg, int *opt, int *offset)
{
	t_ast	*tmp;
	char	*str;
	int		ret;

	tmp = *ast;
	str = tmp->str;
	while (tmp)
	{
		ret = -1;
		if (str[0] == '-' && ((str[1] == '-' && !str[2]) ||
		!str[1]))
			return (0);
		if (str[0] == '-' && (ret = options(tmp, opt, offset)))
			return (1);
		else if (tmp->str[0] == '-' && ret == 0 && (*opt & S))
		{
			*arg = tmp->right && tmp->right->str ?
			ft_strdup(tmp->right->str) : NULL;
			return (0);
		}
		tmp = tmp->right;
	}
	return (0);
}

int			ft_history(t_ast **ast, t_env **env)
{
	int		opt;
	int		offset;
	char	*arg;

	(void)env;
	opt = 0;
	offset = 0;
	arg = NULL;
	if ((*ast)->right)
		io_seq(&(*ast)->right->right, 1);
	if ((*ast)->left->right && parse_opt(&(*ast)->left->right,
	&arg, &opt, &offset))
		return (0);
	run_his(arg, opt, offset, (*his_slg())->n ? his_len(his_slg()) : 0);
	return (1);
}
