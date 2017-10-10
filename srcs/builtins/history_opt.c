/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 12:26:29 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 21:14:34 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	no_options(t_his **his, int offset, int his_len)
{
	t_his	*tmp;
	int		nbr;
	int		len;

	(void)offset;
	(void)his_len;
	if (!(*his))
		return ;
	tmp = (*his)->n;
	nbr = 1;
	len = his_len - offset;
	if (offset < 0 || offset > his_len)
		return ;
	if (!offset)
		offset = his_len - 1;
	nbr = his_len - offset - (offset == his_len - 1 ? 0 : 1);
	while (tmp->n && --offset)
		tmp = tmp->n;
	while (tmp->p)
	{
		ft_printf("%5d  %s\n", nbr++, tmp->cmdl);
		tmp = tmp->p;
	}
}

void		hist_read(t_his **his, int offset, int his_len, char *arg)
{
	char	*line;
	int		fd;

	(void)his;
	(void)offset;
	(void)arg;
	(void)his_len;
	line = NULL;
	if ((fd = open(".42sh_history", O_RDONLY)) == -1)
	{
		fd_printf(2, "Error while opening .42sh_history\n");
		return ;
	}
	while (get_next_line(fd, &line))
	{
		cmd_save_history(line);
		ft_strdel(&line);
	}
}

void		hist_append(t_his **his, int offset, int his_len, char *arg)
{
	t_his	*tmp;
	int		fd;

	(void)offset;
	(void)his_len;
	(void)arg;
	tmp = *his;
	if (!tmp->n)
		return ;
	while (tmp->n)
		tmp = tmp->n;
	if ((fd = open(".42sh_history", O_RDWR | O_APPEND | O_CREAT, 0700)) == -1)
	{
		fd_printf(2, "Could no write history list to history file\n");
		return ;
	}
	while (tmp->p)
	{
		ft_putendl_fd(tmp->cmdl, fd);
		tmp = tmp->p;
	}
	close(fd);
}

static void	hist_del(t_his **his, int offset, int his_len, char *arg)
{
	t_his	*tmp;

	(void)his_len;
	(void)arg;
	tmp = *his;
	if (!tmp || offset > his_len)
		return ;
	while (tmp->n)
		tmp = tmp->n;
	while (--offset)
		tmp = tmp->p;
	if (tmp->p)
		tmp->p->n = tmp->n;
	if (tmp->n)
		tmp->n->p = tmp->p;
	ft_strdel(&tmp->cmdl);
	free(tmp);
}

void		run_his(char *arg, int opt, int offset, int his_len)
{
	int					i;
	static const t_hist	option[7] = {{1, &hist_clear}, {2, &hist_del},
	{4, &hist_append}, {8, &hist_read}, {16, &hist_read}, {32, &hist_write},
	{128, &hist_sarg}};

	i = -1;
	if (!opt)
		no_options(his_slg(), offset, his_len);
	else
		while (++i < 7)
			if (opt & option[i].op)
				option[i].f(his_slg(), offset, his_len, arg);
}
