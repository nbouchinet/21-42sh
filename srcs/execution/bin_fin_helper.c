/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fin_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 16:21:23 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/30 18:54:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

char	**creat_arg(t_ast **ast, char *cmd)
{
	int		i;
	int		j;
	char	**arg;
	t_ast	*tmp;

	i = 0;
	tmp = NULL;
	if ((i = count_arg_node(&(*ast)) + 1) >= 2)
		tmp = *ast;
	if (!(arg = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	arg[0] = ft_strdup(cmd);
	j = 1;
	while (tmp && j < i + 1)
	{
		arg[j] = ft_strdup(tmp->str);
		tmp = tmp->right;
		j++;
	}
	arg[i] = NULL;
	return (arg);
}
