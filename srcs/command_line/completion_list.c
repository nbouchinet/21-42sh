/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:17:12 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/01 13:17:14 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		display_e(t_ls *list, t_win **win, char **cmd, int k)
{
	char			*save;
	int				i;

	if (list && list_len(&list) > 1)
	{
		i = call_print_lst(win, cmd, list, 1);
		return (i);
	}
	else if (list)
	{
		save = ft_strdup((*cmd) + ((*win)->cur - (*win)->pr));
		(*cmd)[k + (k ? 1 : 0)] = 0;
		(*cmd) = ft_strjoinf((*cmd), (list)->name, 1);
		(*cmd) = ft_strjoinf((*cmd), save, 3);
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		write(1, (*cmd) + ((*win)->cur - (*win)->pr), ft_strlen((*cmd) + ((*win)->cur - (*win)->pr)));
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		while (SEP && (*cmd)[(*win)->cur - (*win)->pr])
			arrow_rigth(*win, *cmd);
		list_del(&list);
		return (1);
	}
	return (0);
}

int 			list_exe(char *tmp, char **path, t_win **win, char **cmd, int k)
{
	struct dirent	*rdd;
	DIR				*dir;
	t_ls			*list;
	int				i;

	if ((*win)->hd || (*win)->quote)
		return (0);
	list = NULL;
	i = -1;
	while (path[++i])
	{
		dir = opendir(path[i]);
		while ((rdd = readdir(dir)) != 0)
		{
			if (ft_strncmp(rdd->d_name, tmp, ft_strlen(tmp)) == 0)
				!list ? list = fill_lst(&list, rdd, 1) :
				fill_lst(&list, rdd, 1);
		}
		closedir(dir);
	}
	i = display_e(list, win, cmd, k);
	ft_free(path, NULL);
	return (i);
}

static char			*get_path(char **str)
{
	char		*path;
	char		*temp;
	int			i;
	int			save;

	save = 0;
	i = -1;
	while ((*str)[++i])
		if ((*str)[i] == '/')
			save = i;
	if ((*str)[save] == '/')
	{
		path = ft_strsub((*str), 0, save + 1);
		temp = (*str);
		if ((*str)[save + 1])
			(*str) = ft_strsub((*str), save + 1, ft_strlen((*str) + save));
		else
			(*str) = NULL;
		free(temp);
	}
	else
		path = ft_strdup(".");
	return (path);
}

static void     display_f(t_ls *list, char **cmd, char *path, t_win **win)
{
	char			*save;

	if (list && list_len(&list) > 1)
	{
		call_print_lst(win, cmd, list, 0);
		return ;
	}
	else if (list)
	{
		save = ft_strdup((*cmd) + ((*win)->cur - (*win)->pr));
		OR_SEP ? arrow_left(*win) : 0;
		while (SEP && (*win)->cur - (*win)->pr)
			arrow_left(*win);
		(*cmd)[(*win)->cur - (*win)->pr + ((*win)->cur - (*win)->pr ? 1 : 0)] = 0;
		path[0] != '.' ? (*cmd) = ft_strjoinf((*cmd), path , 1) : 0;
		(*cmd) = ft_strjoinf((*cmd), (list)->name, 1);
		(*cmd) = ft_strjoinf((*cmd), save, 3);
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		write(1, (*cmd) + ((*win)->cur - (*win)->pr),
		ft_strlen((*cmd) + ((*win)->cur - (*win)->pr)));
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		arrow_rigth(*win, *cmd);
		while (SEP && (*cmd)[(*win)->cur - (*win)->pr])
			arrow_rigth(*win, *cmd);
	}
	else
		beep();
	list_del(&list);
}

void			list_files(char **tmp, t_win **win, char **cmd)
{
	struct dirent	*rdd;
	DIR				*dir;
	t_ls			*list;
	char			*path;

	list = NULL;
	path = (*tmp) ? get_path(tmp) : ft_strdup(".");
	dir = opendir(path);
	while ((rdd = readdir(dir)) != 0)
		if (!(*tmp) || (ft_strncmp(rdd->d_name, (*tmp), ft_strlen(*tmp)) == 0
			&& ft_strcmp(rdd->d_name, ".") && ft_strcmp(rdd->d_name, "..")))
			!list ? list = fill_lst(&list, rdd, 2) : fill_lst(&list, rdd, 2);
	closedir(dir);
    display_f(list, cmd, path, win);
	free(path);
}
