/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 13:58:10 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/21 15:38:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		isexec(char *path)
{
	struct stat buf;

	if (lstat(path, &buf) == -1)
		return (0);
	if ((buf.st_mode & S_IXUSR) && !S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

// void	ft_freetab(char **trash)
// {
// 	int		i;
//
// 	i = -1;
// 	if (!trash)
// 		return ;
// 	while (trash[++i])
// 		ft_strdel(&trash[i]);
// 	free(trash);
// }

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

int		find_bin(t_ast **ast)
{
	char	*dir;

	dir = get_dir((*ast)->str);
	if (binary_finder(dir, (*ast)->str) == 1)
	{
		free(dir);
		return (1);
	}
	free(dir);
	return (0);
}

char	*binary_find(char *cmd, char **path)
{
	int		i;
	char	*bin;
	DIR		*dir;

	i = -1;
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
	return (NULL);
}

int		find_cmd_bin(t_ast **ast, char **path)
{
	char	*cmd;

	if ((cmd = binary_find((*ast)->str, path)))
	{
		free((*ast)->str);
		(*ast)->str = ft_strdup(cmd);
		free(cmd);
		return (1);
	}
	return (0);
}

int		count_arg_node(t_ast **ast)
{
	int		i;
	t_ast	*tmp;

	i = 0;
	if (*ast)
	{
		tmp = *ast;
		while (tmp)
		{
			i++;
			tmp = tmp->right;
		}
	}
	return (i);
}
