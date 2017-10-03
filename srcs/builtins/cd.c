/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:08:34 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/02 17:41:15 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		mod_env(t_env **env, char *path, char *save)
{
	t_env		*tmp;

	tmp = lst_at(env, "OLDPWD");
	if (tmp)
	{
		ft_strdel(&tmp->value);
		if (lst_at(env, "PWD"))
			tmp->value = ft_strdup(lst_at(env, "PWD")->value);
		else
			tmp->value = ft_strdup(save);
	}
	tmp = lst_at(env, "PWD");
	if (tmp)
	{
		ft_strdel(&tmp->value);
		tmp->value = ft_strdup(path);
	}
}

static int change_dir(t_ast **ast, int opt, char **path)
{
	t_ast			*tmp;
	struct stat		st;
	char			*buff;
	char			*bs;
	int				i;

	tmp = *ast;
	buff = NULL;
	i = 0;
	while (tmp && tmp->str[0] == '-' && tmp->str[1])
		tmp = tmp->right;
	if (stat((*path), &st) == -1)
		return (fd_printf(2, "cd: no such file or directory: %@\n", tmp->str));
	if (S_ISDIR(st.st_mode) || (i = S_ISLNK(st.st_mode)))
	{
		if ((access((*path), R_OK)) == -1)
			return (fd_printf(2, "cd: permission denied: %@\n", tmp->str));
		if (chdir((*path)) == -1)
			return (fd_printf(2, "cd: %@:not a directoryn", tmp->str));
		if (i && opt == 1)
		{
			readlink((*path), buff, 1024);
			bs = ft_strrchr((*path), '/');
			*(bs + 1) = 0;
			(*path) = ft_strjoinf((*path), buff, 1);
		}
	}
	else
		return (fd_printf(2, "cd: %@: not a directory\n", tmp->str));
	return (0);
}

static void build_path(t_env **env, char *str, char **path)
{
	char	**rp;
	int		i;
	int		len;

	i = -1;
	*path = ft_strdup(lst_at(env, "PWD")->value);
	*path[ft_strlen(*path) - (*path)[0] ? 1 : 0] == '/' ?
	*path[ft_strlen(*path) - (*path)[0] ? 1 : 0]  = 0: 0;
	rp = ft_strsplit(str, '/');
	while (rp[++i])
	{
		len = 0;
		if (rp[i][0] == '.' && rp[i][1] == '.' && rp[i][2] == 0)
		{
			len = ft_strlen((*path));
			while ((*path)[--len])
				if ((*path)[len] == '/')
					break ;
			(*path)[len + (len ? 0 : 1)] = 0;
		}
		else
			(*path) = (*path)[ft_strlen((*path))] == '/' ? ft_strjoinf((*path),
			rp[i], 3) : ft_strjoinf(ft_strjoinf((*path), "/", 1), rp[i], 1);
	}
	ft_free(rp, NULL, 1);
}

static int	get_arg(t_ast **ast, t_env **env, char **path)
{
	char	*match;
	t_ast	*tmp;

	match = NULL;
	tmp = *ast;
	while (tmp && tmp->str[0] == '-' && tmp->str[1])
		tmp = tmp->right;
	if (tmp && tmp->str && tmp->str[ft_strlen(tmp->str) - 1] == '/')
		tmp->str[ft_strlen(tmp->str) - 1] = 0;
	else if (!tmp && lst_at(env, "HOME"))
		*path = ft_strdup(lst_at(env, "HOME")->value);
	else if (tmp && tmp->str[0] == '-' && !tmp->str[1])
		*path = ft_strdup(lst_at(env, "OLDPWD")->value);
	else if ((tmp && !(match = ft_strstr(tmp->str, ".."))) ||
	(match && match[2] != 0 && match[2] != '/'))
	{
		if (tmp->str[0] == '/')
			*path = ft_strdup(tmp->str);
		else if (tmp->str[0] == '.' && !tmp->str[1])
			(*path) = ft_strdup(lst_at(env, "PWD")->value);

		else
		{
			if (lst_at(env, "PWD") && (match = lst_at(env, "PWD")->value))
				(*path) = match[ft_strlen(match) - 1] == '/' ?
				ft_strjoin(match, tmp->str)	: ft_strjoinf(ft_strjoin
				(match, "/"), tmp->str, 1);
			else if (getcwd(match, MAXPATHLEN))
				(*path )= match[ft_strlen(match) - 1] == '/' ? ft_strjoin(match,
				tmp->str) : ft_strjoinf(ft_strjoin(match, "/"), tmp->str, 1);
		}
	}
	if (!*path)
		build_path(env, tmp->str, path);
	return (0);
}

static int	get_opt(t_ast **ast, int *opt)
{
	t_ast	*tmp;
	int		i;

	tmp = *ast;
	i = 0;
	while (tmp)
	{
		if (tmp->str && tmp->str[0] == '-' && tmp->str[1] == '-' && !tmp->str[2])
			return (0);
		while (tmp->str[++i] && tmp->str[i] == '-')
			if (tmp->str[i] == 'P')
				(*opt) = 1;
			else if (tmp->str[i] == 'L')
				(*opt) = 2;
			else
				return (fd_printf(2, "cd: -%c: invalid option\n",
				tmp->str[i]));
		tmp = tmp->right;
	}
	return (0);
}

static int	check_arg(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

	tmp = *ast;
	while (tmp && tmp->str[0] == '-' && tmp->str[1])
		tmp = tmp->right;
	if (tmp && tmp->right && !tmp->right->right)
		return (fd_printf(2, "cd: string not in pwd: %s\n", tmp->str));
	else if (tmp && tmp->right && tmp->right->right)
		return (fd_printf(2, "cd: too many arguments\n"));
	else if ((*env && !lst_at(env, "OLDPWD") && tmp && tmp->str[0] == '-' &&
	!tmp->str[1]) || (*env && !lst_at(env, "PWD") && tmp && tmp->str[0] == '-'
	&& !tmp->str[1]))
		return (fd_printf(2, "cd: OLDPWD not set\n"));
	else if (*env && !lst_at(env, "HOME") && !tmp)
		return (fd_printf(2, "cd: HOME not set\n"));
	return (0);
}

int			ft_cd(t_ast **ast, t_env **env)
{
	char	*path;
	char	*current_dir;
	int		opt;

	path = NULL;
	current_dir = NULL;
	opt = 2;
	current_dir = getcwd(current_dir, MAXPATHLEN);
	if (check_arg(&(*ast)->left->right, env))
		return (0);
	if ((*ast)->left->right && get_opt(&(*ast)->left->right, &opt))
		return (0);
	if (get_arg(&(*ast)->left->right, env, &path))
		return (0);
	if (change_dir(&(*ast)->left->right, opt, &path))
	{
		ft_strdel(&path);
		ft_strdel(&current_dir);
		return (0);
	}
	mod_env(env, path, current_dir);
	ft_strdel(&path);
	ft_strdel(&current_dir);
	return (1);
}
