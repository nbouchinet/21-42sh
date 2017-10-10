/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:08:34 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 21:13:09 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	malloc_env_lnk(t_env **env, t_env **tmp)
{
	if (*env)
	{
		(*tmp) = *env;
		while ((*tmp) && (*tmp)->next)
			(*tmp) = (*tmp)->next;
		if (!((*tmp)->next = (t_env *)ft_memalloc(sizeof(t_env))))
			exit(EXIT_FAILURE);
		(*tmp) = (*tmp)->next;
	}
	else
	{
		if (!((*tmp) = (t_env *)ft_memalloc(sizeof(t_env))))
			exit(EXIT_FAILURE);
		*env = (*tmp);
	}
}

static char	*construct_path(t_env **env, char *save, char *path)
{
	char		*np;
	char		*ptr;
	char		**array;
	char		**save_array;

	np = path[0] == '/' ? NULL : ft_strdup(save);
	array = NULL;
	if (!ft_strcmp(path, "-"))
		return (lst_at(env, "OLDPWD")->value);
	else if (!ft_strcmp(path, "."))
		return (lst_at(env, "PWD")->value);
	array = ft_strsplit(path, '/');
	save_array = array;
	while (*array)
	{
		if (!ft_strcmp(*array, ".."))
		{
			if ((ptr = ft_strrchr(np, '/')))
				*ptr = 0;
			else
			{
				np ? ft_strdel(&np) : 0;
				ft_free(save_array, NULL, 1);
				return (ft_strdup("/"));
			}
		}
		else if (ft_strcmp(*array, ".") && ft_strcmp(*array, "-"))
		{
			np = np ? ft_strjoinf(np, "/", 1) : ft_strjoin(np, "/");
			np = ft_strjoinf(np, *array, 1);
		}
		array++;
	}
	ft_free(save_array, NULL, 1);
	return (np);
}

static void	mod_env(t_env **env, char *path, char *save)
{
	t_env		*tmp;

	if ((tmp = lst_at(env, "OLDPWD")))
		ft_strdel(&tmp->value);
	else
	{
		malloc_env_lnk(env, &tmp);
		tmp->var = ft_strdup("OLDPWD");
	}
	tmp->value = lst_at(env, "PWD") ? ft_strdup(lst_at(env, "PWD")->value) :
	ft_strdup(save);
	if ((tmp = lst_at(env, "PWD")))
		ft_strdel(&tmp->value);
	else
	{
		malloc_env_lnk(env, &tmp);
		tmp->var = ft_strdup("PWD");
	}
	tmp->value = construct_path(env, save, path);
}

static int	change_dir(t_env **env, t_ast **ast, int opt, char **path)
{
	t_ast			*tmp;
	struct stat		st;
	char			buff[MAXPATHLEN];
	char			*bs;
	int				i;

	tmp = *ast;
	i = 0;
	ft_memset(buff, 0, MAXPATHLEN);
	while (tmp && tmp->str[0] == '-' && tmp->str[1])
		tmp = tmp->right;
	if (lstat((*path), &st) == -1)
			return (fd_printf(2, "cd: %s: no such file or directory\n",
			tmp && tmp->str ? tmp->str : lst_at(env, "HOME")->value));
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

static int	get_arg(t_ast **ast, t_env **env, char **path)
{
	t_ast	*tmp;

	tmp = *ast;
	while (tmp && tmp->str[0] == '-' && tmp->str[1])
		tmp = tmp->right;
	if (!tmp && lst_at(env, "HOME"))
		*path = ft_strdup(lst_at(env, "HOME")->value);
	else if (tmp && tmp->str[0] == '-' && !tmp->str[1])
		*path = ft_strdup(lst_at(env, "OLDPWD")->value);
	else
		*path = ft_strdup(tmp->str);
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
		if (tmp->str && ((tmp->str[0] == '-' && tmp->str[1] == '-' &&
		!tmp->str[2]) || (tmp->str[0] != '-')))
			return (0);
		while (tmp->str[++i])
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
	!tmp->str[1]))
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
	if ((check_arg(&(*ast)->left->right, env)) ||
	((*ast)->left->right && get_opt(&(*ast)->left->right, &opt)) ||
	((*ast)->left->right && get_arg(&(*ast)->left->right, env, &path)))
		return (0);
	current_dir = getcwd(current_dir, MAXPATHLEN);
	if (!path)
		path = lst_at(env, "HOME") ? ft_strdup(lst_at(env, "HOME")->value) : NULL;
	if (change_dir(env, &(*ast)->left->right, opt, &path))
	{
		ft_strdel(&path);
		ft_strdel(&current_dir);
		return (0);
	}
	mod_env(env, path, current_dir);
	ft_strdel(&current_dir);
	ft_strdel(&path);
	return (1);
}
