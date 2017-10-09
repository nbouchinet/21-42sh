/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 02:35:16 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/09 19:02:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_env	*find_node(t_env **env, char *var, char *value)
{
	t_env	*tmp;

	tmp = *env;
	if (var != NULL)
		while (tmp && ft_strcmp(tmp->var, var) != 0)
			tmp = tmp->next;
	else
		while (tmp && ft_strcmp(tmp->value, value) != 0)
			tmp = tmp->next;
	return (tmp);
} // 1

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
} // 0

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
} // 0

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
