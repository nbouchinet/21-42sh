/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_opt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:06:43 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/18 18:06:45 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void hist_sarg(t_his **his, int offset, int his_len, char *arg)
{
	int		fd;

	(void)his;
	(void)offset;
	(void)his_len;
	if ((fd = open(".42sh_history", O_RDWR | O_APPEND | O_CREAT, 0700)) == -1)
	{
		fd_printf(2, "Could no write history list to history file\n");
		return ;
	}
	ft_putendl_fd(arg, fd);
	close(fd);
}

void 	hist_write(t_his **his, int offset, int his_len, char *arg)
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
