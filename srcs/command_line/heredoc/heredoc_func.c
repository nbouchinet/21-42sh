/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 18:46:35 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 18:46:36 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

void				cmp_herestring(char **cmd, t_hdoc *tmp, int fdt[])
{
	if (ft_strcmp((*cmd), tmp->hstring))
	{
		write(1, "\nheredoc> ", 10);
		write(fdt[1], (*cmd), ft_strlen(*cmd));
		g_loop = 1;
	}
	else
	{
		tmp->hstring ? ft_strdel(&tmp->hstring) : 0;
		tmp && tmp->next ? write(1, "\nheredoc> ", 10) : 0;
		g_loop = tmp && tmp->next ? 256 : 0;
		close(fdt[0]);
		fdt[0] = -2;
		fdt[1] = -2;
	}
}

static int			check_here_string(char *hstring)
{
	if (!hstring || hstring[0] == '<' || hstring[0] == '&' ||
			hstring[0] == ';' || hstring[0] == '>' || hstring[0] == ')' ||
			hstring[0] == '|')
	{
		fd_printf(2, "\nsyntax error near unexpected token `%c'", hstring[0]);
		g_loop = 0;
		return (0);
	}
	else
	{
		g_loop = 1;
		return (1);
	}
}

void				call_chs(t_win **win, char **save)
{
	t_hdoc	*tmp;

	tmp = (*win)->hd;
	while (tmp)
		if (!(check_here_string(tmp->hstring)))
		{
			save_history(*win, save, &(*win)->his);
			ft_free(NULL, save);
			return ;
		}
		else
			tmp = tmp->next;
	(*win)->cur = 9;
	(*win)->pr = 9;
	write(1, "\nheredoc> ", 10);
}
