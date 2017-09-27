/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:49:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/27 15:01:36 by zadrien          ###   ########.fr       */
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

static int	get_offset(char **targ, int i, int j, int *offset)
{
	int		ret;

	ret = 1;
	if (targ[i][j + 1] != 0 &&
	(ret = only(targ[i] + (j + 1), '0', '9')))
		(*offset) = ft_atoi(targ[i] + (j + 1));
	else if (targ[i][j + 1] && !ret)
		return (fd_printf(2, "42sh: history: -d: %s: "
		"history position out of range\n", targ[i] + (j + 1)));
	else if (targ[i + 1] && (ret = only(targ[i + 1], '0', '9')))
		(*offset) = ft_atoi(targ[i + 1]);
	else if (targ[i + 1] && !ret)
		return (fd_printf(2, "42sh: history: -d: %s: "
		"history position out of range\n", targ[i + 1]));
	else
		return (fd_printf(2, "42sh: history: -d: option "
		"requires an argument\n"));
	return (0);
}

static int	options(char **arg, int i, int *opt, int *offset)
{
	int		j;

	j = 0;
	while (arg[i][++j])
	{
		if (!ft_strchr("cdanrwps", arg[i][j]))
			return (fd_printf(2, "history: -%c: %s\n%s%s",
			arg[i][j], HO, HU1, HU2));
		if (arg[i][j] == 'd' && ((*opt) |= D) && get_offset(arg, i, j, offset))
			return (1);
		else if (arg[i][j] == 'd' && ((*opt) |= D))
			break ;
		arg[i][j] == 'c' ? (*opt) |= C : 0;
		arg[i][j] == 'a' ? (*opt) |= A : 0;
		arg[i][j] == 'n' ? (*opt) |= N : 0;
		arg[i][j] == 'r' ? (*opt) |= R : 0;
		arg[i][j] == 'w' ? (*opt) |= W : 0;
		arg[i][j] == 'p' ? (*opt) |= P : 0;
		if (arg[i][j] == 's')
		{
			(*opt) |= S;
			return (0);
		}
	}
	if (opt_check(opt, 4, 3, 0))
		return (1);
	return (0);
}

static int	parse_opt(char *targ[], int *opt, int *offset, char **arg)
{
	int		ret;
	int		i;

	i = -1;
	while (targ[++i])
	{
		ret = -1;
		if (targ[i][0] == '-' && ((targ[i][1] == '-' && !targ[i][2])
		|| !targ[i][1]))
			return (0);
		if (targ[i][0] == '-' && (ret = options(targ, i, opt, offset)))
			return (1);
		else if (targ[i][0] == '-' && ret == 0)
		{
			if (*opt & S)
			{
				*arg = ft_strdup(targ[i + 1]);
				return (0);
			}
		}
		else
		{
			if (only(targ[i], '0', '9'))
				(*offset) = ft_atoi(targ[i]);
			else
				return (fd_printf(2, "history: %s: numeric argument required\n"
				, targ[i]));
		}
	}
	return (0);
}

int         ft_history(t_ast **ast, t_env **env)
{
	int		opt;
	int		offset;
	char	**targ;
	char	*arg;

	(void)env;
	opt = 0;
	offset = 0;
	arg = NULL;
	(*ast)->right ? io_seq(&(*ast)->right->right) : 0;
	if ((targ = creat_arg_env(&(*ast)->left->right)) && parse_opt(targ, &opt,
	&offset, &arg))
		return (0);
	ft_printf("opt: %d | offset: %d\n", opt, offset);
	ft_printf("arg: %s\n", arg);
	run_his(arg, opt, offset, (*his_slg())->n ? his_len(his_slg()) : 0);
	return (1);
}
