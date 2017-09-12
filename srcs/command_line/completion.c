/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 15:42:48 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/11 20:10:20 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		list_exec(t_cmdl *cmdl, char *tmp, char *arr_path[])
{
	struct dirent	*rdd;
	DIR				*dir;
	t_comp			*comp;
	int				i;

	comp = NULL;
	i = -1;
	if (cmdl->opt & CSQ || cmdl->opt & CDQ /*|| cmdl->hd*/)
		return (0);
	while (arr_path[++i])
	{
		if (!(dir = opendir(arr_path[i])))
			return (1);
		while ((rdd = readdir(dir)) != 0)
		{
			if (ft_strncmp(rdd->d_name, tmp, ft_strlen(tmp)) == 0 &&
			!check_comp(&comp, rdd->d_name))
				!comp ? comp = fill_comp(&comp, rdd, 1) :
				fill_comp(&comp, rdd, 1);
		}
		closedir(dir);
	}
	return (display_comp(cmdl, &comp, ft_strlen(tmp)));
}


static void		list_files(t_cmdl *cmdl, char **tmp)
{
	struct dirent	*rdd;
	DIR				*dir;
	t_comp			*comp;
	char			*path;

	comp = NULL;
	path = (*tmp ? get_path(tmp) : ft_strdup("."));
	if (!(dir = opendir(path)))
		return ;
	while ((rdd = readdir(dir)) != 0)
	if (!(*tmp) || (ft_strncmp(rdd->d_name, (*tmp), ft_strlen(*tmp)) == 0
		&& ft_strcmp(rdd->d_name, ".") && ft_strcmp(rdd->d_name, "..")))
		if (rdd->d_name[0] != '.' || ft_strlen((*tmp)))
				!comp ? comp = fill_comp(&comp, rdd, 2) :
				fill_comp(&comp, rdd, 2);
	closedir(dir);
	free(path);
	if (comp)
		display_comp(cmdl, &comp, ft_strlen(*tmp));
}

static void 	get_comp(t_cmdl *cmdl, int i)
{
	char 	*tmp;
	char	**path;

	path = ft_strsplit(lst_at(&cmdl->lstenv, "PATH")->value, ':');
	while (--i > 0 && cmdl->line.str[i] != ' ' && cmdl->line.str[i] != '|' &&
	cmdl->line.str[i] != ';' && cmdl->line.str[i] != '&' &&
	cmdl->line.str[i] != '<' && cmdl->line.str[i] != '>')
		;
	i += (i < 0 ? 1 : 0);
	while (cmdl->line.str[cmdl->line.cur - cmdl->line.pr] && sep(cmdl, 0))
		arrow_rigth(cmdl);
	if (cmdl->line.str[cmdl->line.cur - cmdl->line.pr - 1] != ' ')
		tmp = ft_strsub(cmdl->line.str, (i ? i + 1 : i),
		cmdl->line.cur - cmdl->line.pr - i - (i ? 1 : 0));
	else
		tmp = NULL;
	if (tmp && is_exec(cmdl))
		list_exec(cmdl, tmp, path) ? 0 : list_files(cmdl, &tmp);
	else
		list_files(cmdl, &tmp);
	if (tmp)
		free(tmp);
	ft_free(path, NULL, 1);
}

static int		only_space(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	write(1, "\033[1mRTFM\n", 9);
	print_prompt();
	return (1);
}

int				completion(t_cmdl *cmdl)
{
	int		i;

	i = cmdl->line.cur - cmdl->line.pr;
	if (cmdl->opt & CHICS_CS)
		return (return_cmdl(cmdl));
	if (!(cmdl->opt & CSQ)  && !(cmdl->opt & CDQ) && !(cmdl->opt & CPIPE) &&
	    !(cmdl->opt & ANCD) && !(cmdl->opt & COR)/*&& cmdl->hd */ &&
	    (!cmdl->lstenv || !lst_at(&cmdl->lstenv, "PATH") ||
	only_space(cmdl->line.str)))
		return (1);
	if (i - 1 < 0 || cmdl->line.str[i - 1] != '|' ||
	cmdl->line.str[i - 1] != ';' || cmdl->line.str[i - 1] != '&' ||
	cmdl->line.str[i - 1] != '<' || cmdl->line.str[i - 1] != '>')
		get_comp(cmdl, cmdl->line.cur - cmdl->line.pr);
	return (1);
}
