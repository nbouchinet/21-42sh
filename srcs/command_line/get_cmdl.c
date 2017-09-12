/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 18:34:00 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 09:33:41 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void exit_cmdl(t_cmdl *cmdl)
{
	char	*s1;

	if (cmdl->line.save)
	{
		s1 = cmdl->line.str;
		cmdl->line.str = ft_strtrimf(ft_strjoin(cmdl->line.save,
		cmdl->line.str));
		free(s1);
		ft_strdel(&cmdl->line.save);
	}
	cmd_save_history(cmdl->line.str);
	cmdl->opt |= CRESET;
	cmd_history(cmdl);
	if (cmdl->line.str)
		end(cmdl);
	if (cmdl->opt & CCTRLD)
		write(1, "\n", 1);
}

static void get_op(t_cmdl *cmdl, int *ret, int *i)
{
	static const	t_op		op[20] = {{{-61, -89, 0, 0}, &ccp},
	{{-30, -120, -102, 0}, &ccp}, {{-30, -119, -120, 0}, &ccp},
	{{27, 91, 68, 0}, &arrow_left}, {{27, 91, 67, 0}, &arrow_rigth},
	{{27, 91, 72, 0}, &home}, {{27, 91, 70, 0}, &end},
	{{27, 27, 91, 68}, &opt_left}, {{27, 27, 91, 67}, &opt_right},
	{{27, 27, 91, 65}, &up_dwn}, {{27, 27, 91, 66}, &up_dwn},
				          {{27, 91, 65, 0}, &cmd_history}, {{27, 91, 66, 0}, &cmd_history},
				          {{10, 0, 0, 0}, &return_cmdl}, {{127, 0, 0, 0}, &del},
				          {{18, 0, 0, 0}, &cmd_search_history}, {{14, 0, 0, 0}, &cmd_search_history},
				          {{9, 0, 0, 0}, &completion}, {{1, 0, 0, 0}, &home}, {{5, 0, 0, 0}, &end}};


	*ret = 0;
	*i = -1;
	ft_memset(cmdl->line.buf, '\0', 6);
	read(0, cmdl->line.buf, 6);
	while (++(*i) < 20)
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
		else if (i == 20)
			print(cmdl, cmdl->line.buf);
		// ft_printf("buf: %d %d %d %d\n", cmdl->line.buf[0], cmdl->line.buf[1],
  // 		cmdl->line.buf[2], cmdl->line.buf[3]);
	}
	exit_cmdl(cmdl);
}
