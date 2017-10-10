/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 18:33:54 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 11:49:59 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_type_bin(t_ast **ast, t_env **env)
{
	if ((*ast)->left->type == CMD_NAME_ABS)
		return (check_abs_bin((*ast)->left->str));
	else if ((*ast)->left->type == CMD_NAME_RLT)
		return (check_rlt_bin(&(*ast)->left->str, env));
	return (0);
}

int		check_file(DIR *dir, char *directory, char **str)
{
	struct dirent	*file;

	while ((file = readdir(dir)))
		if (isnt_dot(file->d_name, *str))
		{
			ft_strdel(str);
			*str = ft_strjoin(directory, "/");
			*str = ft_strjoinf(*str, file->d_name, 1);
			if (check_abs_bin(*str) == 1)
			{
				closedir(dir);
				return (1);
			}
		}
	closedir(dir);
	return (0);
}

int		exist_bin(char **str, char *value)
{
	int		i;
	DIR		*dir;
	char	**path;

	if ((path = ft_strsplit(value, ':')))
	{
		i = -1;
		while (path[++i])
			if ((dir = opendir(path[i])))
				if (check_file(dir, path[i], str))
				{
					ft_freetab(path);
					return (1);
				}
	}
	ft_freetab(path);
	return (-3);
}

int		check_rlt_bin(char **str, t_env **env)
{
	t_env	*tmp;

	if ((tmp = find_node(env, "PATH", NULL)))
		return (tmp->value ? exist_bin(str, tmp->value) : -2);
	return (-1);
}

char	**creat_argv(t_ast **ast)
{
	int		i;
	char	**argv;
	t_ast	*tmp;

	i = 1;
	tmp = *ast;
	i = nbr_arg(&tmp->right) + i;
	if (!(argv = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	argv[i] = NULL;
	argv[0] = ft_strdup(tmp->left->str);
	if (tmp->right)
	{
		i = 0;
		tmp = tmp->right;
		while (tmp)
		{
			argv[++i] = ft_strdup(tmp->str);
			tmp = tmp->right;
		}
	}
	return (argv);
}
