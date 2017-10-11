/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 18:09:00 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 16:36:24 by zadrien          ###   ########.fr       */
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
	{
		while (tmp && ft_strcmp(tmp->value, value) != 0)
			tmp = tmp->next;
	}
	return (tmp);
}

int		check_abs_bin(char *str)
{
	struct stat buf;

	if (!lstat(str, &buf))
	{
		ft_putendl("HEllo");
		if (!S_ISDIR(buf.st_mode))
			if (S_IXUSR & buf.st_mode)
				return (1);
		return (-3);
	}
	else
		perror("lstat ");
	return (-3);
}

int		isnt_dot(char *file, char *str)
{
	if (!ft_strcmp(str, ".") || !ft_strcmp(str, ".."))
		return (0);
	else if (!ft_strcmp(file, str))
		return (1);
	return (0);
}

int		nbr_arg(t_ast **ast)
{
	t_ast	*tmp;
	int		i;

	i = 0;
	if (*ast)
	{
		tmp = *ast;
		while (tmp)
		{
			tmp = tmp->right;
			i++;
		}
	}
	return (i);
}

int		print_error(int err, char *str)
{
	if (err == -1)
		ft_errormsg("42sh: ", NULL, "Path not set.");
	else if (err == -2)
		ft_errormsg("42sh: ", NULL, "Path's value not set.");
	else if (err == -3)
		ft_errormsg("42sh: ", str, ": Command not found.");
	else if (err == 1)
		return (1);
	return (0);
}
