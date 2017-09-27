/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 18:34:00 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 12:17:58 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	exit_cmdl(t_cmdl *cmdl)
{
	char	*s1;

	ft_putendl("0");
	if (cmdl->line.save)
	{
		ft_putendl("0.0");
		s1 = cmdl->line.str;
		ft_putendl("0.1");
		cmdl->line.str = ft_strtrimf(ft_strjoin(cmdl->line.save,
		cmdl->line.str));
		ft_putendl("0.2");
		free(s1);
		ft_putendl("0.4");
		ft_strdel(&cmdl->line.save);
		ft_putendl("0.5");
	}
	ft_putendl("0.6");
	cmd_save_history(cmdl->line.str);
	ft_putendl("0.7");
	cmdl->opt |= CRESET;
	cmd_history(cmdl);
	ft_putendl("0.8");
	cmdl->opt = 0;
	ft_putendl("0.9");
	write(1, "\n", 1);
	ft_putendl("0.10");
}

static void	get_op(t_cmdl *cmdl, int *ret, int *i)
{
	static const	t_op		op[23] = {{{-61, -89, 0, 0}, &ccp},
	{{-30, -120, -102, 0}, &ccp}, {{-30, -119, -120, 0}, &ccp},
	{{27, 91, 68, 0}, &arrow_left}, {{27, 91, 67, 0}, &arrow_right},
	{{27, 91, 72, 0}, &home}, {{27, 91, 70, 0}, &end},
	{{27, 27, 91, 68}, &opt_left}, {{27, 27, 91, 67}, &opt_right},
	{{27, 27, 91, 65}, &up_dwn}, {{27, 27, 91, 66}, &up_dwn},
	{{27, 91, 65, 0}, &cmd_history}, {{27, 91, 66, 0}, &cmd_history},
	{{10, 0, 0, 0}, &return_cmdl}, {{127, 0, 0, 0}, &del},
	{{18, 0, 0, 0}, &cmd_search_history}, {{14, 0, 0, 0}, &cmd_search_history},
	{{9, 0, 0, 0}, &completion}, {{1, 0, 0, 0}, &home}, {{5, 0, 0, 0}, &end},
	{{21, 0, 0, 0}, &ctrl_u}, {{20, 0, 0, 0}, &ctrlt}, {{27, 0, 0, 0}, &esc}};

	*ret = 0;
	*i = -1;
	ft_memset(cmdl->line.buf, '\0', 6);
	read(0, cmdl->line.buf, 6);
	while (++(*i) < 23)
	if (cmdl->line.buf[0] == op[(*i)].key[0] &&
		cmdl->line.buf[1] == op[(*i)].key[1]
		&& cmdl->line.buf[2] == op[(*i)].key[2] &&
		cmdl->line.buf[3] == op[(*i)].key[3]
		&& cmdl->line.buf[4] == op[(*i)].key[4])
			if (((*ret) = op[(*i)].f(cmdl)))
				break ;
}

void		get_cmdl(t_cmdl *cmdl)
{
	int				i;
	int				ret;

	ret = 0;
	print_prompt();
	while (1)
	{
		i = -1;
		cmdl_signals(cmdl);
		get_op(cmdl, &ret, &i);
		if (ret == 2)
			break ;
		else if (CTRL_L(cmdl->line.buf))
			ctrl_l(cmdl);
		else if (CTRL_D(cmdl->line.buf))
		{
			if (ctrl_d(cmdl))
				return ;
		}
		else if (i == 23)
			print(cmdl, cmdl->line.buf);
	}
	exit_cmdl(cmdl);
}
