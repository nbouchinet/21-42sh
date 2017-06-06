/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:08:34 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/03 14:08:45 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_env 	*lst_at(t_env **env, char *cmp)
{
	t_env	*tmp;

	tmp = *env;
	if (tmp && !tmp->var)
		return (NULL);
	while (tmp->next && ft_strcmp(tmp->var, cmp))
		tmp = tmp->next;
	return (tmp);
}

static void		mod_env(t_env **env, char buff[], int opt)
{
	t_env		*tmp;

	(void)opt;
	tmp = lst_at(env, "OLDPWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(buff);
	}
	tmp = lst_at(env, "PWD");
	if (tmp)
	{
		free(tmp->value);
		getcwd(buff, 1024);
		tmp->value = ft_strdup(buff);
	}
}

static int		chdirectory(char *path)
{
	struct stat	st;

	if (lstat(path, &st) == -1)
		return (fd_printf(2, "cd: no such file or directory: %@\n", path));
	if (S_ISDIR(st.st_mode) || S_ISLNK(st.st_mode))
	{
		if ((access(path, R_OK)) == -1)
			return (fd_printf(2, "cd: permission denied: %@\n", path));
		if (chdir(path) == -1)
			return (fd_printf(2, "cd: not a directory: %@\n", path));
	}
	else
		return (fd_printf(2, "cd: not a directory: %@\n", path));
	return (0);
}


static int		get_opt(char **arg, int *i, int *opt)
{
	int		j;

	while (arg[(*i)] && arg[(*i)][0] == '-')
	{
		j = 0;
		if (arg[(*i)][0] == '-' && ((arg[(*i)][1] == '-' && arg[(*i)][2] == 0)
		|| arg[(*i)][1] == 0))
			return (0);
		while (arg[(*i)][++j])
			if (arg[(*i)][j] == 'P')
				(*opt) = 1;
			else if (arg[(*i)][j] == 'L')
				(*opt) = 2;
			else
				return (fd_printf(2, "cd: -%c: invalid option\n", arg[(*i)][j]));
		(*i) += 1;
	}
	return (0);
}

static int		check(t_env **env, char **arg, int *opt, char **path)
{
	t_env	*tmp;
	int		len;
	int 	i;

	i = 0;
	if (arg && get_opt(arg, &i, opt))
		return (1);
	len = ft_tablen(arg + i);
	if (len == 2)
		return (fd_printf(2, "cd: string not in pwd: %s\n", arg[i]));
	else if (len > 2)
		return (fd_printf(2, "cd: too many arguments\n"));
	if (!(tmp = lst_at(env, "PWD")) && arg && arg[i][0] == '-' && arg[i][1] == 0)
		return (fd_printf(2, "cd: OLDPWD not set\n"));
	else if (!(tmp = lst_at(env, "OLDPWD")) && arg && arg[i][0] == '-' && arg[i][1] == 0)
		return (fd_printf(2, "cd: OLDPWD not set\n"));
	else if (!(tmp = lst_at(env, "HOME")) && arg && arg[0][0] == '~')
		return (fd_printf(2, "cd: HOME not set\n"));
	if (i == 0 && !arg)
		(*path) = lst_at(env, "HOME")->value;
	else if (arg[i][0] == '-' && arg[i][1] == 0)
		(*path) = lst_at(env, "OLDPWD")->value;
	else
		(*path) = arg[i];
	return (0);
}

int     		ft_cd(t_ast **ast, t_env **env)
{
	char	**arg;
	char	*path;
	char	buff[1024];
	int		opt;

	opt = 2;
	arg = creat_arg_env(&(*ast)->right);
	if (check(env, arg, &opt, &path) != 0)
		return (1);
	if (chdirectory(path))
		return (1);
	getcwd(buff, 1024);
	mod_env(env, buff, opt);
	return (0);
}