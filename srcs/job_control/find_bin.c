/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 18:33:54 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/06 19:11:20 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		print_error(int err, char *str)
{
	if (err == -1)
		ft_errormsg("42sh: ", NULL, "Path not set.");
	else if (err == -2)
		ft_errormsg("42sh: ", NULL, "Path's value not set.");
	else if (err == -3)
		ft_errormsg("42sh: ", str, ": Command not found.");
	return (0);
}

int		check_type_bin(t_ast **ast, t_env **env)
{
	if ((*ast)->left->type == CMD_NAME_ABS)
		return (check_abs_bin((*ast)->left->str));
	else if ((*ast)->left->type == CMD_NAME_ABS)
		return (check_rlt_bin((*ast)->left->str), env);
	return (0);
}

int		check_abs_bin(char *str)
{
	struct stat buf;

	if (!lstat(str, &buf))
	{
		if (S_ISREG(buf.st_mode))
			if (S_IXUSR & buf.st_mode)
				return (1);
		return (-3);
	}
	else
		perror("lstat ");
	return (0);
}

int		exist_bin(char **str, char **value)
{
	int		i;
	DIR		*dir;
	char	**path;

	if ((path = ft_strsplit(*value, ':')))
	{
		i = -1;
		while (path[++i])
		{
			if ((dir = opendir(path[i])))
				check_file(dir, str);
		}
	}
}
int		check_rlt_bin(char **str, t_env **env)
{
	t_env	*tmp;

	if ((tmp = find_node(env, "PATH", NULL)))
	{
		if (tmp->value)
		{
			exist_bin(str, tmp->value);
		}
		return (-2);
	}
	return (-1);
}
