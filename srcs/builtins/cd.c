/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:08:34 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/11 14:58:06 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	change_dir(t_env **env, t_ast **ast, int opt, char **path)
{
	t_ast			*tmp;
	struct stat		st;

	tmp = *ast;
	while (tmp && tmp->str[0] == '-' && tmp->str[1])
		tmp = tmp->right;
	if (lstat((*path), &st) == -1)
	{
		return (fd_printf(2, "cd: %s: no such file or directory\n",
		tmp && tmp->str ? tmp->str : lst_at(env, "HOME")->value));
	}
	if (S_ISDIR(st.st_mode) || S_ISLNK(st.st_mode))
		return (just_norme(&st, tmp, path, opt));
	else
		return (fd_printf(2, "cd: %@: not a directory\n", tmp->str));
	return (0);
}

static int	get_arg(t_ast **ast, t_env **env, char **path, char *save)
{
	t_ast	*tmp;
	t_env	*home;

	tmp = *ast;
	home = lst_at(env, "HOME");
	while (tmp && tmp->str[0] == '-' && tmp->str[1])
		tmp = tmp->right;
	if (!tmp && home && !home->value)
		return (1);
	else if (!tmp && home)
		*path = ft_strdup(home->value);
	else if (tmp && tmp->str[0] == '-' && !tmp->str[1])
		*path = ft_strdup(lst_at(env, "OLDPWD")->value);
	else
		*path = construct_path(env, save, tmp->str);
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
			{
				return (fd_printf(2, "cd: -%c: invalid option\n",
				tmp->str[i]));
			}
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
	else if (*env && !lst_at(env, "PWD") && tmp && tmp->str[0] == '.' &&
	!tmp->str[1])
		return (1);
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
	current_dir = (*cmdl_slg())->pwd;
	if ((check_arg(&(*ast)->left->right, env)) ||
	((*ast)->left->right && get_opt(&(*ast)->left->right, &opt)) ||
	(get_arg(&(*ast)->left->right, env, &path, current_dir)))
		return (0);
	if (change_dir(env, &(*ast)->left->right, opt, &path))
	{
		ft_strdel(&path);
		return (0);
	}

	mod_env(env, path, current_dir);
	ft_strdel(&(*cmdl_slg())->pwd);
	(*cmdl_slg())->pwd = ft_strdup(path);
	ft_strdel(&path);
	return (1);
}
