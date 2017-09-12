/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:08:34 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 18:42:44 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		mod_env(t_env **env, char *path)
{
	t_env		*tmp;

	tmp = lst_at(env, "OLDPWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(lst_at(env, "PWD")->value);
	}
	tmp = lst_at(env, "PWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(path);
	}
	free(path);
}

static int		chdirectory(char **path, int opt, char *arg)
{
	struct stat		st;
	char			buff[1024];
	char			*bs;
	int				i;

	if (lstat((*path), &st) == -1)
		return (fd_printf(2, "cd: no such file or directory: %@\n", arg));
	if (S_ISDIR(st.st_mode) || (i = S_ISLNK(st.st_mode)))
	{
		if ((access((*path), R_OK)) == -1)
			return (fd_printf(2, "cd: permission denied: %@\n", arg));
		if (chdir((*path)) == -1)
			return (fd_printf(2, "cd: %@:not a directoryn", arg));
		if (i && opt == 1)
		{
			readlink((*path), buff, 1024);
			bs = ft_strrchr((*path), '/');
			*(bs + 1) = 0;
			(*path) = ft_strjoinf((*path), buff, 1);
		}
	}
	else
		return (fd_printf(2, "cd: %@: not a directory\n", arg));
	return (0);
}

static int		get_opt(char **arg, int *i, int *opt)
{
	int		j;

	(*i) = 0;
	while (arg[(*i)] && arg[(*i)][0] == '-')
	{
		j = 0;
		if (arg[(*i)][0] == '-' && ((arg[(*i)][1] == '-' && arg[(*i)][2] == 0)
		|| arg[(*i)][1] == 0))
			return (0);
		while (arg[(*i)][++j])
		{
			if (arg[(*i)][j] == 'P')
				(*opt) = 1;
			else if (arg[(*i)][j] == 'L')
				(*opt) = 2;
			else
				return (fd_printf(2, "cd: -%c: invalid option\n",
				arg[(*i)][j]));
		}
		(*i) += 1;
	}
	return (0);
}

static void		build_path(char **path, char *arg, t_env **env)
{
	char	**rpath;
	int		i;
	int		len;

	i = -1;
	(*path) = ft_strdup(lst_at(env, "PWD")->value);
	(*path)[ft_strlen(*path) - 1] == '/' ?
	(*path)[ft_strlen(*path) - 1] = 0 : 0;
	rpath = ft_strsplit(arg, '/');
	while (rpath[++i])
	{
		len = 0;
		if (rpath[i][0] == '.' && rpath[i][1] == '.' && rpath[i][2] == 0)
		{
			len = ft_strlen((*path));
			while ((*path)[--len])
				if ((*path)[len] == '/')
					break ;
			(*path)[len + (len ? 0 : 1)] = 0;
		}
		else
			(*path) = (*path)[ft_strlen((*path))] == '/' ?
			ft_strjoinf((*path), rpath[i], 3) :
			ft_strjoinf(ft_strjoin((*path), "/"), rpath[i], 1);
	}
}

static void		cd_get_path(t_env **lstenv, char *arg, char **path)
{
	char	*tmp;

	tmp = NULL;
	if (arg)
		arg[ft_strlen(arg) - 1] == '/' ? arg[ft_strlen(arg) - 1] = 0 : 0;
	if (!arg)
		(*path) = ft_strdup(lst_at(lstenv, "HOME")->value);
	else if (arg[0] == 0)
		(*path) = ft_strdup("/");
	else if (arg[0] == '-' && arg[1] == 0)
		(*path) = ft_strdup(lst_at(lstenv, "OLDPWD")->value);
	else if ((!(tmp = ft_strstr(arg, ".."))) ||
	(tmp && tmp[2] != 0 && tmp[2] != '/'))
	{
		if (arg[0] == '/')
			(*path) = ft_strdup(arg);
		else if (arg[0] == '.' && arg[1] == 0)
			(*path) = ft_strdup(lst_at(lstenv, "PWD")->value);
		else
		{
			tmp = lst_at(lstenv, "PWD")->value;
			(*path) = tmp[ft_strlen(tmp) - 1] == '/' ? ft_strjoin(tmp, arg)
			: ft_strjoinf(ft_strjoin(tmp, "/"), arg, 1);
		}
	}
	!(*path) ? build_path(path, arg, lstenv) : 0;
}

static int		check_arg(int len, char *arg, t_env **lstenv)
{
	if (len == 2)
		return (fd_printf(2, "cd: string not in pwd: %s\n", arg));
	else if (len > 2)
		return (fd_printf(2, "cd: too many arguments\n"));
	if ((!(lst_at(lstenv, "PWD"))) && arg && arg[0] == '-' && arg[1] == 0)
		return (fd_printf(2, "cd: OLDPWD not set\n"));
	else if ((!(lst_at(lstenv, "OLDPWD")))
		&& arg && arg[0] == '-' && arg[1] == 0)
		return (fd_printf(2, "cd: OLDPWD not set\n"));
	else if ((!(lst_at(lstenv, "HOME"))) && arg && arg[0] == '~')
		return (fd_printf(2, "cd: HOME not set\n"));
	return (0);
}

int				ft_cd(t_ast **ast, t_env **env)
{
	char	**targ;
	char	*arg;
	char	*path;
	int		opt;
	int		i;

	opt = 2;
	i = 0;
	path = NULL;
	targ = creat_arg_env(&(*ast)->left->right);
	if ((targ && get_opt(targ, &i, &opt))
		|| (check_arg(i ? ft_tablen(targ + i) : 0, i ? targ[i] : NULL, env)))
		return (0);
	arg = targ ? targ[i] : NULL;
	cd_get_path(env, arg, &path);
	if (chdirectory(&path, opt, arg))
		return (0);
	mod_env(env, path);
	ft_free(targ, NULL);
	return (1);
}
