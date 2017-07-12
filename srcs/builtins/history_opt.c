/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 12:26:29 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/08 12:26:42 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void        hist_clear(t_his **his, int offset, int len)
{
	t_his 	*tmp;
	t_his	*save;

	(void)offset;
	(void)len;
	tmp = *his;
	if (!tmp)
		return ;
	while (tmp)
	{
		save = tmp->next;
		ft_strdel(&tmp->cmdl);
		free(tmp);
		tmp = save;
	}
	if (!((*his) = (t_his *)malloc(sizeof(t_his))))
		exit(fd_printf(2, "malloc error\n"));
	(*his)->cmdl = ft_strdup("");
	(*his)->add = 1;
	(*his)->prev = NULL;
	(*his)->next = NULL;
}

void        hist_del(t_his **his, int offset, int len)
{
	t_his 	*tmp;
	t_his	*save_prev;

	tmp = *his;
	if (offset > len)
	{
		fd_printf(2, "history: %d: %s\n", offset, HM);
		return ;
	}
	while (offset--)
	{
		save_prev = tmp;
		tmp = tmp->next;
	}
	ft_strdel(&tmp->cmdl);
	save_prev->next = tmp->next;
	tmp->next->prev = save_prev;
	free(tmp);
}

void		hist_append(t_his **his, int offset, int len)
{
	int			fd;
	t_his		*tmp;

	(void)offset;
	(void)len;
	if (!(*his))
		return ;
	while ((*his)->prev)
		(*his) = (*his)->prev;
	tmp = (*his);
	if ((fd = open(".42sh_history", O_RDWR | O_APPEND | O_CREAT, 0700)) == -1)
			fd_printf(2, "Could no write history list to history file\n");
	if (fd)
		while (tmp)
		{
			!tmp->add ? ft_putendl_fd(tmp->cmdl, fd) : 0;
			tmp = tmp->next;
		}
	fd != -1 ? close(fd) : 0;
}

static void	add_to_hist(t_his **his, char *line, t_his *tmp, int i)
{
	if (!i)
	{
		if (!(tmp = (t_his *)malloc(sizeof(t_his))))
		exit(fd_printf(2, "malloc error\n"));
		tmp->cmdl = ft_strdup(line);
		tmp->add = 0;
		tmp->prev = NULL;
		tmp->next = (*his);
		(*his)->prev = tmp;
		return ;
	}
	while ((*his)->next)
		(*his) = (*his)->next;
	tmp = (*his);
	(*his) = (*his)->prev;
	if (!((*his)->next = (t_his *)malloc(sizeof(t_his))))
		exit(fd_printf(2, "save-hisroty: malloc error\n"));
	(*his)->next->cmdl = ft_strdup(line);
	(*his)->next->add = 0;
	(*his)->next->prev = (*his);
	(*his)->next->next = tmp;
	(*his) = (*his)->next;
	(*his)->next->prev = (*his);
	(*his) = (*his)->next;
}

void		hist_read(t_his **his, int offset, int len)
{
	char	*line;
	int		fd;
	t_his	*head;
	t_his	*tmp;

	(void)offset;
	(void)len;
	line = NULL;
	head = *his;
	tmp = NULL;
	if ((fd = open(".42sh_history", O_RDONLY)) == -1)
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(*his)->next && !(*his)->prev)
			add_to_hist(his, line, tmp, 0);
		else
			add_to_hist(his, line, tmp, 1);
		ft_strdel(&line);
	}
}

void		hist_sarg(t_his **his, int offset, int len)
{
	int			fd;
	t_his		*tmp;

	(void)offset;
	(void)len;
	if (!(*his))
		return ;
	while ((*his)->prev)
		(*his) = (*his)->prev;
	tmp = (*his);
	if ((fd = open(".42sh_history", O_RDWR | O_APPEND | O_CREAT, 0700)) == -1)
			fd_printf(2, "Could no write history list to history file\n");
	while (tmp && fd != -1)
	{
		!tmp->add ? ft_putstr_fd(tmp->cmdl, fd) : 0;
		tmp->add = 1;
		tmp = tmp->next;
	}
	ft_putendl_fd("", fd);
	fd != -1 ? close(fd) : 0;
}