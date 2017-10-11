/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 19:04:21 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/11 19:04:28 by khabbar          ###   ########.fr       */
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

static int	construct_path_utils(char **array, char **np, char **save_array)
{
	char	*ptr;

	if (!ft_strcmp(*array, ".."))
	{
		if ((ptr = ft_strrchr(*np, '/')) && *(ptr + 1))
			*(ptr + (ptr == *np ? 1 : 0)) = 0;
		else
		{
			*np ? ft_strdel(np) : 0;
			ft_free(save_array, NULL, 1);
			return (1);
		}
	}
	else if (ft_strcmp(*array, ".") && ft_strcmp(*array, "-"))
	{
		*np = *np ? ft_strjoinf(*np, "/", 1) : ft_strjoin(*np, "/");
		*np = ft_strjoinf(*np, *array, 1);
	}
	return (0);
}

char		*construct_path(t_env **env, char *save, char *path)
{
	char		*np;
	char		**array;
	char		**save_array;

	if (!ft_strcmp(path, "-"))
		return (ft_strdup(lst_at(env, "OLDPWD")->value));
	else if (!ft_strcmp(path, "."))
		return (ft_strdup(lst_at(env, "PWD")->value));
	np = path[0] == '/' ? NULL : ft_strdup(save);
	array = NULL;
	array = ft_strsplit(path, '/');
	save_array = array;
	while (*array)
	{
		if (construct_path_utils(array, &np, save_array))
			return (ft_strdup("/"));
		array++;
	}
	ft_free(save_array, NULL, 1);
	return ((np ? np : ft_strdup("/")));
}

void		mod_env(t_env **env, char *path, char *save)
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
	tmp->value = ft_strdup(path);
}

int 	just_norme(struct stat *st, t_ast *tmp, char **path, int opt)
{
	char			*bs;
	char			buff[MAXPATHLEN];

	ft_memset(buff, 0, MAXPATHLEN);
	if (!(S_IXUSR & st->st_mode))
		return (fd_printf(2, "cd: permission denied: %@\n", tmp->str));
	if (chdir((*path)) == -1)
		return (fd_printf(2, "cd: %@: not a directory\n", tmp->str));
	if (S_ISLNK(st->st_mode) && opt == 1)
	{
		readlink((*path), buff, 1024);
		bs = ft_strrchr((*path), '/');
		bs ? *(bs + 1) = 0 : 0;
		(*path) = ft_strjoinf((*path), buff, 1);
	}
	return (0);
}
