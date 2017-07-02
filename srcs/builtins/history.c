/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:49:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:54:43 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check_opt(int opt)
{

}

static int  get_opt(char **arg, int *opt, int *offset)
{
	int     i;
	int     j;

	i = -1;
	while (arg[++i] && arg[i][0] == '-')
	{
		j = 0;
		if (arg[i][0] == '-' && ((arg[i][1] == '-' && arg[i][2] == 0)
		|| arg[i][1] == 0))
			return (0);
		if (!ft_isdigit(arg[i]))
			while (arg[i][++j])
			{
				arg[i][j] == 'c' ? (*opt) |= C : 0;
				arg[i][j] == 'd' ? (*opt) |= D : 0;
				arg[i][j] == 'a' ? (*opt) |= A : 0;
				arg[i][j] == 'n' ? (*opt) |= N : 0;
				arg[i][j] == 'r' ? (*opt) |= R : 0;
				arg[i][j] == 'w' ? (*opt) |= W : 0;
				arg[i][j] == 'p' ? (*opt) |= P : 0;
				arg[i][j] == 's' ? (*opt) |= S : 0;
				if (!ft_strchr("cdanrwps", arg[i][j]))
					return (fd_printf(2, "history: -%c: invalid option\n%s",
					arg[i][j], HIS_USAGE));
			}
	}
	return (0);
}

int         history(t_ast **ast)
{
	char	**targ;
	int		opt;
	int		offset;

	offset = -1;
	targ = creat_arg_env(&(*ast)->right);
	if ((targ && get_opt(targ, &opt, &offset)) || check_opt(opt))
		return (0);
}