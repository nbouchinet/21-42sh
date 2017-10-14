/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 15:42:48 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/06 11:43:42 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		list_exec(t_cmdl *cmdl, char *tmp, char *arr_path[])
{
	struct dirent	*rdd;
	DIR				*dir;

	while (*arr_path++)
	{
		if (!(dir = opendir(*arr_path)))
			continue ;
		while ((rdd = readdir(dir)) != 0)
			if (ft_strncmp(rdd->d_name, tmp, ft_strlen(tmp)) == 0 &&
			!check_comp(&cmdl->comp, rdd->d_name))
				!cmdl->comp ? cmdl->comp = fill_comp(&cmdl->comp, rdd, 2, 0) :
				fill_comp(&cmdl->comp, rdd, 2, 0);
		closedir(dir);
	}
	check_built_in(cmdl, tmp);
	cmdl->comp ? cmdl->comp->bol = 1 : 0;
	if (cmdl->comp)
		return (display_comp(cmdl, &cmdl->comp, ft_strlen(tmp)));
	write(2, "\7", 1);
	return (0);
}

static void		list_files(t_cmdl *cmdl, char **tmp)
{
	struct dirent	*rdd;
	DIR				*dir;
	char			*path;

	path = (*tmp ? get_path(tmp) : ft_strdup("."));
	if (!(dir = opendir(path)))
	{
		ft_strdel(&path);
		return ;
	}
	while ((rdd = readdir(dir)) != 0)
		if (!(*tmp) || (ft_strncmp(rdd->d_name, (*tmp), ft_strlen(*tmp)) == 0
		&& ft_strcmp(rdd->d_name, ".") && ft_strcmp(rdd->d_name, "..")))
			if (rdd->d_name[0] != '.' || ft_strlen((*tmp)))
				!cmdl->comp ? cmdl->comp = fill_comp(&cmdl->comp, rdd, 2, 0) :
				fill_comp(&cmdl->comp, rdd, 2, 0);
	closedir(dir);
	ft_strdel(&path);
	if (cmdl->comp && (cmdl->comp->bol = 1))
		display_comp(cmdl, &cmdl->comp, ft_strlen(*tmp));
	else
		write(2, "\7", 1);
}

static void		get_comp(t_cmdl *cmdl, int i)
{
	char	*tmp;
	char	**path;

	path = ft_strsplit(lst_at(&cmdl->lstenv, "PATH")->value, ':');
	while (--i > 0 && cmdl->line.str[i] != ' ' && cmdl->line.str[i] != '|' &&
			cmdl->line.str[i] != ';' && cmdl->line.str[i] != '&' &&
			cmdl->line.str[i] != '<' && cmdl->line.str[i] != '>')
		;
	i += (i < 0 ? 1 : 0);
	while (cmdl->line.str[cmdl->line.cur - cmdl->line.pr] && sep(cmdl, 0))
		arrow_right(cmdl);
	if (cmdl->line.str[cmdl->line.cur - cmdl->line.pr - 1] != ' ')
		tmp = ft_strsub(cmdl->line.str, (i ? i + 1 : i),
		cmdl->line.cur - cmdl->line.pr - i - (i ? 1 : 0));
	else
		tmp = NULL;
	if (tmp && tmp[0] == '~' && tmp[1] == '/' && lst_at(&cmdl->lstenv, "HOME"))
		tmp = ft_strjoinf(lst_at(&cmdl->lstenv, "HOME")->value,
		ft_strdups(tmp + 1, &tmp), 2);
	if (tmp && is_exec(cmdl))
		list_exec(cmdl, tmp, path) ? 0 : list_files(cmdl, &tmp);
	else
		list_files(cmdl, &tmp);
	ft_free(path, tmp ? &tmp : NULL, tmp ? 3 : 1);
}

static int		only_space_comp(char *str)
{
	while (*str)
		if (*(++str) != ' ')
			return (0);
	write(2, "\033[1mRTFM\033[0m\n", 13);
	print_prompt();
	return (write(2, "\7", 1));
}

int				completion(t_cmdl *cmdl)
{
	int		i;

	if (cmdl->opt & CCP)
		return (write(2, "\7", 1));
	i = cmdl->line.cur - cmdl->line.pr;
	if (cmdl->comp && (cmdl->opt & CCOMP))
		return (c_move(&cmdl->comp));
	else
		comp_del(&cmdl->comp);
	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
	if (!cmdl->lstenv || !lst_at(&cmdl->lstenv, "PATH") ||
	only_space_comp(cmdl->line.str))
		return (1);
	if (i - 1 < 0 || cmdl->line.str[i - 1] != '|' ||
	cmdl->line.str[i - 1] != ';' || cmdl->line.str[i - 1] != '&' ||
	cmdl->line.str[i - 1] != '<' || cmdl->line.str[i - 1] != '>')
		get_comp(cmdl, cmdl->line.cur - cmdl->line.pr);
	return (1);
}
