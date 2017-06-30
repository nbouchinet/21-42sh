/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fin_help2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 09:56:26 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/30 18:53:56 by zadrien          ###   ########.fr       */
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

char	*get_dir(char *cmd)
{
	int		i;
	int		index;
	char	*ncmd;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '/')
			index = i;
	i = -1;
	if (!(ncmd = ft_strnew(index + 1)))
		return (NULL);
	while (++i <= index)
		ncmd[i] = cmd[i];
	return (ncmd);
}

int		ft_checkbin(DIR *dir, char *cmd)
{
	struct dirent *dirp;

	while ((dirp = readdir(dir)))
		if (ft_strcmp(dirp->d_name, ".") != 0 &&
			ft_strcmp(dirp->d_name, "..") != 0)
			if (ft_strcmp(dirp->d_name, cmd) == 0)
				return (1);
	return (0);
}

int		binary_finder(char *path, char *cmd)
{
	DIR		*dir;

	if ((dir = opendir(path)))
		if (ft_checkbin(dir, ft_strrchr(cmd, '/') + 1) == 1)
			if (isexec(cmd) == 1)
			{
				closedir(dir);
				return (1);
			}
	closedir(dir);
	return (0);
}

char	*create_path(char *env, char *cmd)
{
	int		i;
	char	*str;

	i = ft_strlen(env) + ft_strlen(cmd);
	if (!(str = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	ft_bzero(str, i + 2);
	ft_strcat(str, env);
	i = ft_strlen(env);
	if (env[i - 1] != '/')
		ft_strcat(str, "/");
	ft_strcat(str, cmd);
	return (str);
}
