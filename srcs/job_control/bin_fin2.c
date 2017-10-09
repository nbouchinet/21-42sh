/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 02:37:55 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/09 18:57:02 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		isexec(char *path)
{
	struct stat buf;

	if (lstat(path, &buf) == -1)
		return (0);
	if ((buf.st_mode & S_IXUSR) && !S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

int		binary_finder(char *path, char *cmd)
{
	DIR		*dir;

	if ((dir = opendir(path)))
	{
		if (ft_checkbin(dir, ft_strrchr(cmd, '/') + 1) == 1)
			if (isexec(cmd) == 1)
			{
				closedir(dir);
				return (1);
			}
		closedir(dir);
	}
	return (0);
}

char	*binary_find(char *cmd, char **path)
{
	int		i;
	char	*bin;
	DIR		*dir;

	i = -1;
	if (path)
	{
		while (path[++i])
			if ((dir = opendir(path[i])))
			{
				if (ft_checkbin(dir, cmd) == 1)
				{
					bin = create_path(path[i], cmd);
					closedir(dir);
					if (isexec(bin) == 1)
						return (bin);
					free(bin);
					return (NULL);
				}
				closedir(dir);
			}
	}
	return (NULL);
}

int		countnode(t_env *env)
{
	int		i;

	i = 0;
	if (!env)
		return (i);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
