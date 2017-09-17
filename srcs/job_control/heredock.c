/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:19:32 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/17 18:15:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int 	hd_ret(t_cmdl *cmdl)
{
	(void)cmdl;
	return (2);
}

static void		get_op(t_cmdl *cmdl, int *ret, int *i)
{
	static const	t_op		op[16] = {{{-61, -89, 0, 0}, &ccp},
	{{-30, -120, -102, 0}, &ccp}, {{-30, -119, -120, 0}, &ccp},
	{{27, 91, 68, 0}, &arrow_left}, {{27, 91, 67, 0}, &arrow_rigth},
	{{27, 91, 72, 0}, &home}, {{27, 91, 70, 0}, &end},
	{{27, 27, 91, 68}, &opt_left}, {{27, 27, 91, 67}, &opt_right},
	{{27, 27, 91, 65}, &up_dwn}, {{27, 27, 91, 66}, &up_dwn},
	{{127, 0, 0, 0}, &del}, {{9, 0, 0, 0}, &completion},
	{{1, 0, 0, 0}, &home}, {{5, 0, 0, 0}, &end}, {{10, 0, 0, 0}, &hd_ret}};

	*ret = -1;
	*i = -1;
	ft_memset(cmdl->line.buf, '\0', 6);
	read(0, cmdl->line.buf, 6);
	while (++(*i) < 16)
		if (cmdl->line.buf[0] == op[(*i)].key[0] &&
		cmdl->line.buf[1] == op[(*i)].key[1]
		&& cmdl->line.buf[2] == op[(*i)].key[2] &&
		cmdl->line.buf[3] == op[(*i)].key[3]
		&& cmdl->line.buf[4] == op[(*i)].key[4])
			if (((*ret) = op[(*i)].f(cmdl)))
				break ;
}

// TESTER LE CTRL-C

static int		engage_heredoc(t_tok **stop, t_cmdl *cmdl, int i, int ret)
{
	int		p[2];

	if (pipe(p) == -1)
		return (fd_printf(2, "heredoc: pipe error\n"));
	print_prompt();
	while (1)
	{
		get_op(cmdl, &ret, &i);
		if (ret == 2 && !(ft_strcmp(cmdl->line.str, (*stop)->str)))
			break ;
		else if (ret == 2)
		{
			write(p[1], cmdl->line.str, ft_strlen(cmdl->line.str));
			write(p[1], "\n", 1);
			ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
			print_prompt();
		}
		else if (CTRL_L(cmdl->line.buf))
			ctrl_l(cmdl);
		else if (CTRL_D(cmdl->line.buf) && ctrl_d(cmdl))
				return (-1);
		else if (i == 16)
			print(cmdl, cmdl->line.buf);
	}
	close(p[1]);
	return(p[0]);
}

t_tok	*heredoc(t_tok **lst)
{
	t_tok	*tmp;
	t_cmdl	*cmdl;

	if (*lst)
	{
		tmp = *lst;
		while (tmp)
		{
			if (tmp->type == BBDIR)
			{
				if (tmp->n && tmp->n->type == WORD)
				{
					cmdl = *cmdl_slg();
					init_cmdl();
					cmdl->opt |= CHD;
					if ((tmp->n->hd = engage_heredoc(&tmp->n, cmdl, -1, -1)) == -1)
						return (*lst);
				}
				else
					return (tmp->n);
			}
			tmp = tmp->n;
		}
	}
	return (NULL);
}
