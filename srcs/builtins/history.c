/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:49:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:54:43 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	exec_hist(int opt, int offset, t_his *his, int len)
{
	int				nbr;
	int				i;
	static const	t_hist	option[7] = {{1, &hist_clear}, {2 , &hist_del},
	{4, &hist_append}, {8, &hist_read}, {16, &hist_read}, {32, &hist_append},
	{128, &hist_sarg}};

	nbr = 0;
	i = -1;
	while (++i < 7)
		opt & option[i].op ? option[i].f(&his, offset, len) : 0;
	if (i == 7 && !opt && (!offset || offset > len))
		while (his && ft_strcmp(his->cmdl, ""))
		{
			ft_printf("    %d  %s\n", ++nbr, his->cmdl);
			his = his->next;
		}
	else if (i == 7 && !opt && offset)
	{
		len = len - offset;
		while (--len)
		{
			his = his->next;
			nbr += 1;
		}
		while (his && ft_strcmp(his->cmdl, ""))
		{
			ft_printf("    %d  %s\n", ++nbr, his->cmdl);
			his = his->next;
		}
	}
}

static int	is_digit(char *str)
{
	int		i;

	i = -1;
	if (str[0] == 0)
		return (1);
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

static int	options(char **arg, int i, int *opt, int *offset)
{
	int     j;

	j = 0;
	while (arg[i][++j])
	{
		arg[i][j] == 'c' ? (*opt) |= C : 0;
		if (arg[i][j] == 'd')
		{
			(*opt) |= D;
			if (is_digit(arg[i] + (j + 1)))
				(*offset) = ft_atoi(arg[i] + (j + 1));
			else
				return (fd_printf(2, "history: %s: %s\n", arg[i] + j + 1, HM));
			break ;
		}
		arg[i][j] == 'a' ? (*opt) |= A : 0;
		arg[i][j] == 'n' ? (*opt) |= N : 0;
		arg[i][j] == 'r' ? (*opt) |= R : 0;
		arg[i][j] == 'w' ? (*opt) |= W : 0;
		arg[i][j] == 'p' ? (*opt) |= P : 0;
		arg[i][j] == 's' ? (*opt) |= S : 0;
		if (!ft_strchr("cdanrwps", arg[i][j]))
			return (fd_printf(2, "history: -%c: %s\n%s", arg[i][j], HO, HU));
	}
	return (0);
}

static int  get_opt(char **arg, int *opt, int *offset)
{
	int     i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i][0] == '-' && ((arg[i][1] == '-' && arg[i][2] == 0)
		|| arg[i][1] == 0))
			return (0);
		if (arg[i][0] == '-')
		{
			if (options(arg, i, opt, offset))
				return (1);
		}
		else
		{
			if (is_digit(arg[i]))
				(*offset) = ft_atoi(arg[i]);
			else
				return (fd_printf(2, "history: %s: %s\n", arg[i], HM));
		}
	}
	return (0);
}

int         ft_history(t_ast **ast, t_env **env)
{
	char	**targ;
	int		opt;
	int		offset;
	t_his	*his;

	(void)env;
	opt = 0;
	offset = 0;
	his = win_sgt()->his;
	while (his->prev)
		his = his->prev;
	targ = creat_arg_env(&(*ast)->left->right);
	if ((targ && get_opt(targ, &opt, &offset)))
		return (0);
	if (opt == 12 || opt == 28 || opt == 60 || opt == 24 || opt == 40
	|| opt == 20 || opt == 36 || opt == 46 || opt == 48)
	{
		fd_printf(2, "history: cannot use more than one of -anrw\n");
		return (0);
	}
	// ft_printf("opt: %d\noffset: %d\n", opt, offset);
	exec_hist(opt, offset, his, lst_len(his));
	return (1);
}
