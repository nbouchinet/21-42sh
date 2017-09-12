/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 12:26:29 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 10:30:01 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/* /\* void        hist_clear(t_his **his, int offset, int len) *\/ */
/* /\* { *\/ */
/* /\* 	t_his 	*tmp; *\/ */
/* /\* 	t_his	*save; *\/ */

/* /\* 	(void)offset; *\/ */
/* /\* 	(void)len; *\/ */
/* /\* 	tmp = *his; *\/ */
/* /\* 	if (!tmp) *\/ */
/* /\* 		return ; *\/ */
/* /\* 	while (tmp) *\/ */
/* /\* 	{ *\/ */
/* /\* 		save = tmp->n; *\/ */
/* /\* 		ft_strdel(&tmp->cmdl); *\/ */
/* /\* 		free(tmp); *\/ */
/* /\* 		tmp = save; *\/ */
/* /\* 	} *\/ */
/* /\* 	if (!((*his) = (t_his *)malloc(sizeof(t_his)))) *\/ */
/* /\* 		exit(fd_printf(2, "malloc error\n")); *\/ */
/* /\* 	(*his)->cmdl = ft_strdup(""); *\/ */
/* /\* 	(*his)->add = 1; *\/ */
/* /\* 	(*his)->p = NULL; *\/ */
/* /\* 	(*his)->n = NULL; *\/ */
/* /\* 	(*his)->len = 0; *\/ */
/* /\* } *\/ */

/* /\* void        hist_del(t_his **his, int offset, int len) *\/ */
/* /\* { *\/ */
/* /\* 	t_his 	*tmp; *\/ */
/* /\* 	t_his	*save_prev; *\/ */

/* /\* 	save_prev = NULL; *\/ */
/* /\* 	tmp = *his; *\/ */
/* /\* 	if (offset > len) *\/ */
/* /\* 	{ *\/ */
/* /\* 		fd_printf(2, "history: %d: %s\n", offset, HM); *\/ */
/* /\* 		return ; *\/ */
/* /\* 	} *\/ */
/* /\* 	while (offset-- > 1) *\/ */
/* /\* 	{ *\/ */
/* /\* 		save_prev = tmp; *\/ */
/* /\* 		tmp = tmp->n; *\/ */
/* /\* 	} *\/ */
/* /\* 	ft_strdel(&tmp->cmdl); *\/ */
/* /\* 	if (save_prev) *\/ */
/* /\* 		save_prev->n = tmp->n; *\/ */
/* /\* 	else *\/ */
/* /\* 		(*his) = tmp->n; *\/ */
/* /\* 	tmp->n->p = save_prev; *\/ */
/* /\* 	free(tmp); *\/ */
/* /\* } *\/ */

/* /\* void		hist_append(t_his **his, int offset, int len) *\/ */
/* /\* { *\/ */
/* /\* 	int			fd; *\/ */
/* /\* 	t_his		*tmp; *\/ */

/* /\* 	(void)offset; *\/ */
/* /\* 	(void)len; *\/ */
/* /\* 	if (!(*his)) *\/ */
/* /\* 		return ; *\/ */
/* /\* 	while ((*his)->p) *\/ */
/* /\* 		(*his) = (*his)->p; *\/ */
/* /\* 	tmp = (*his); *\/ */
/* /\* 	if ((fd = open(".42sh_history", O_RDWR | O_APPEND | O_CREAT, 0700)) == -1) *\/ */
/* /\* 			fd_printf(2, "Could no write history list to history file\n"); *\/ */
/* /\* 	if (fd) *\/ */
/* /\* 		while (tmp) *\/ */
/* /\* 		{ *\/ */
/* /\* 			!tmp->add ? ft_putendl_fd(tmp->cmdl, fd) : 0; *\/ */
/* /\* 			tmp = tmp->n; *\/ */
/* /\* 		} *\/ */
/* /\* 	fd != -1 ? close(fd) : 0; *\/ */
/* /\* } *\/ */

/* /\* static void	add_to_hist(t_his **his, char *line, t_his *tmp, int i) *\/ */
/* /\* { *\/ */
/* /\* 	if (!i) *\/ */
/* /\* 	{ *\/ */
/* /\* 		if (!(tmp = (t_his *)malloc(sizeof(t_his)))) *\/ */
/* /\* 		exit(fd_printf(2, "malloc error\n")); *\/ */
/* /\* 		tmp->cmdl = ft_strdup(line); *\/ */
/* /\* 		tmp->add = 1; *\/ */
/* /\* 		tmp->p = NULL; *\/ */
/* /\* 		tmp->n = (*his); *\/ */
/* /\* 		(*his)->p = tmp; *\/ */
/* /\* 		return ; *\/ */
/* /\* 	} *\/ */
/* /\* 	while ((*his)->n) *\/ */
/* /\* 		(*his) = (*his)->n; *\/ */
/* /\* 	tmp = (*his); *\/ */
/* /\* 	(*his) = (*his)->p; *\/ */
/* /\* 	if (!((*his)->n = (t_his *)malloc(sizeof(t_his)))) *\/ */
/* /\* 		exit(fd_printf(2, "save-hisroty: malloc error\n")); *\/ */
/* /\* 	(*his)->n->cmdl = ft_strdup(line); *\/ */
/* /\* 	(*his)->n->add = 1; *\/ */
/* /\* 	(*his)->n->p = (*his); *\/ */
/* /\* 	(*his)->n->n = tmp; *\/ */
/* /\* 	(*his) = (*his)->n; *\/ */
/* /\* 	(*his)->n->p = (*his); *\/ */
/* /\* 	(*his) = (*his)->n; *\/ */
/* /\* } *\/ */

/* /\* void		hist_read(t_his **his, int offset, int len) *\/ */
/* /\* { *\/ */
/* /\* 	t_his	*head; *\/ */
/* /\* 	t_his	*tmp; *\/ */
/* /\* 	char	*line; *\/ */
/* /\* 	int		fd; *\/ */
/* /\* 	int		count; *\/ */

/* /\* 	(void)offset; *\/ */
/* /\* 	(void)len; *\/ */
/* /\* 	head = *his; *\/ */
/* /\* 	tmp = NULL; *\/ */
/* /\* 	line = NULL; *\/ */
/* /\* 	len == -50 ? count = 30 : -1; *\/ */
/* /\* 	if ((fd = open(".42sh_history", O_RDONLY)) == -1) *\/ */
/* /\* 		return ; *\/ */
/* /\* 	while (get_next_line(fd, &line) > 0) *\/ */
/* /\* 	{ *\/ */
/* /\* 		if (!(*his)->n && !(*his)->p) *\/ */
/* /\* 			add_to_hist(his, line, tmp, 0); *\/ */
/* /\* 		else *\/ */
/* /\* 			add_to_hist(his, line, tmp, 1); *\/ */
/* /\* 		ft_strdel(&line); *\/ */
/* /\* 		count != -1 ? count -= 1 : 0; *\/ */
/* /\* 		if (!count) *\/ */
/* /\* 			break ; *\/ */
/* /\* 	} *\/ */
/* /\* } *\/ */

/* /\* void		hist_sarg(t_his **his, int offset, int len) *\/ */
/* /\* { *\/ */
/* /\* 	int			fd; *\/ */
/* /\* 	t_his		*tmp; *\/ */

/* /\* 	(void)offset; *\/ */
/* /\* 	(void)len; *\/ */
/* /\* 	if (!(*his)) *\/ */
/* /\* 		return ; *\/ */
/* /\* 	while ((*his)->p) *\/ */
/* /\* 		(*his) = (*his)->p; *\/ */
/* /\* 	tmp = (*his); *\/ */
/* /\* 	if ((fd = open(".42sh_history", O_RDWR | O_APPEND | O_CREAT, 0700)) == -1) *\/ */
/* /\* 			fd_printf(2, "Could no write history list to history file\n"); *\/ */
/* /\* 	while (tmp && fd != -1) *\/ */
/* /\* 	{ *\/ */
/* /\* 		!tmp->add ? ft_putstr_fd(tmp->cmdl, fd) : 0; *\/ */
/* /\* 		tmp->add = 1; *\/ */
/* /\* 		tmp = tmp->n; *\/ */
/* /\* 	} *\/ */
/* /\* 	ft_putendl_fd("", fd); *\/ */
/* /\* 	fd != -1 ? close(fd) : 0; *\/ */
/* /\* } *\/ */
