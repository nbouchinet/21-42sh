/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <hpelat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:33:50 by hpelat            #+#    #+#             */
/*   Updated: 2017/06/30 17:50:19 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

void				heredoc(char **cmd, t_win **win, char buf[])
{
	static int		fdt[2] = {-2, -2};
	t_hdoc			*tmp;

	if (EOT)
	{
		g_loop = 0;
		(*win)->hd ? del_hd(&(*win)->hd) : 0;
		return ;
	}
	(*win)->cur = 9;
	(*win)->pr = 9;
	tmp = (*win)->hd;
	while (tmp->next && !tmp->hstring)
		tmp = tmp->next;
	fdt[0] == -2 && pipe(fdt) != -1 ? tmp->fd = ft_itoa(fdt[1]) : 0;
	cmp_herestring(cmd, tmp, fdt);
}

static t_hdoc		*push_basck(char **save, int b, int e, t_hdoc **head)
{
	t_hdoc	*tmp;

	tmp = *head;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_hdoc *)malloc(sizeof(t_hdoc))))
			exit(fd_printf(2, "malloc_error\n"));
		tmp->next->hstring = e == b ? NULL : ft_strsub((*save), b, e - b);
		tmp->next->fd = NULL;
		tmp->next->next = NULL;
		return (tmp->next);
	}
	else
	{
		if (!(tmp = (t_hdoc *)malloc(sizeof(t_hdoc))))
			exit(fd_printf(2, "malloc_error\n"));
		tmp->hstring = e == b ? NULL : ft_strsub((*save), b, e - b);
		tmp->fd = NULL;
		tmp->next = NULL;
	}
	return (tmp);
}

void				get_here_string(char **save, t_win **win, int i, int j)
{
	while ((*save)[++i])
	{
		if ((*save)[i] == '<' && (*save)[i + 1] == '<')
		{
			while ((*save)[i] && (*save)[i] == '<')
				i += 1;
			while ((*save)[i] && (*save)[i] == ' ')
				i += 1;
			j = i;
			while ((*save)[i++] && ((*save)[i] != ' ' && (*save)[i] != '<'))
				;
			if (i == j || (*save)[j] == 0)
			{
				fd_printf(2, "\nsyntax error near unexpected token `newline'");
				save_history(*win, save, &(*win)->his);
				(*save) ? ft_strdel(save) : 0;
				g_loop = 0;
				return ;
			}
			!(*win)->hd ? (*win)->hd = push_basck(save, j, i, &(*win)->hd) :
				push_basck(save, j, i, &(*win)->hd);
			i -= (*save)[i] == '<' ? 1 : 0;
		}
	}
	((*win)->hd) ? call_chs(win, save) : 0;
}
