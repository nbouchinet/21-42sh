/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:33:50 by hpelat            #+#    #+#             */
/*   Updated: 2017/05/02 18:33:53 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

extern int g_loop;

static int				check_here_string(char *hstring)
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

void		heredoc(char **cmd, t_win **win)
{
	t_hdoc	*tmp;

	tmp = (*win)->hd;
	while (tmp->next && !tmp->hstring)
		tmp = tmp->next;
	(*win)->cur = 9;
	(*win)->pr = 9;
	if (ft_strcmp((*cmd), tmp->hstring))
	{
		write(1, "\nheredoc> ", 10);
		tmp->hdoc ? tmp->hdoc = ft_strjoinf(tmp->hdoc, "\n", 1) : 0;
		tmp->hdoc = ft_strjoinf(tmp->hdoc, (*cmd), 1);
		g_loop = 1;
	}
	else
	{
		ft_free(NULL, &tmp->hstring);
		tmp->hdoc ? tmp->hdoc = ft_strjoinf(tmp->hdoc, "\n", 1) : 0;
		tmp && tmp->next ? write(1, "\nheredoc> ", 10) : 0;
		g_loop = tmp && tmp->next ? 1 : 0;
	}
}

static t_hdoc	*push_basck(char **save, int b, int e, t_hdoc **head)
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
		tmp->next->hdoc = NULL;
		tmp->next->next = NULL;
		return (tmp->next);
	}
	else
	{
		if (!(tmp = (t_hdoc *)malloc(sizeof(t_hdoc))))
			exit(fd_printf(2, "malloc_error\n"));
		tmp->hstring = e == b ? NULL : ft_strsub((*save), b, e - b);
		tmp->hdoc = NULL;
		tmp->next = NULL;
	}
	return (tmp);
}

static void	call_chs(t_win **win, char **save)
{
	t_hdoc	*tmp;

	tmp = (*win)->hd;
	while (tmp)
		if (!(check_here_string(tmp->hstring)))
		{
			ft_free(NULL, save);
			return ;
		}
		else
		tmp = tmp->next;
	(*win)->cur = 9;
	(*win)->pr = 9;
	write(1, "\nheredoc> ", 10);
}

void		get_here_string(char **save, t_win **win)
{
	int		i;
	int		j;

	i = -1;
	while ((*save)[++i])
	{
		if ((*save)[i] == '<' && (*save)[i + 1] == '<')
		{
			i += (*save)[i + 2] == '-' ? 3 : 2;
			while ((*save)[i] == ' ')
				i += 1;
			j = i;
			while ((*save)[i] && (*save)[i] != ' ')
				i += 1;
			if (i == j)
			{
				fd_printf(2, "\nsyntax error near unexpected token `newline'");
				g_loop = 0;
				(*save) ? ft_free(NULL, save) : 0;
				return ;
			}
			!(*win)->hd ? (*win)->hd = push_basck(save, j, i, &(*win)->hd) :
			push_basck(save, j, i, &(*win)->hd);
		}
	}
	if (!(*win)->hd)
		return ;
	call_chs(win, save);
}